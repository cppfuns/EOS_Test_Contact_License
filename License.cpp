#include <License.hpp>

void License::setuserinfo(account_name owner, const std::string& company_name, const std::string& contact_info){
    eosio::print("License::setuserinfo line 4");
    require_auth(owner);
    auto account_itr = accounts.find(owner);
    if(account_itr == accounts.end()){
        account_itr = accounts.emplace(_self, [&](auto& account){
            account.name = owner;
            account.company_name = company_name;
            account.contact_info = contact_info;
        });
    }
    else{
        accounts.modify(account_itr, 0, [&](auto& account) {
            account.company_name = company_name;
            account.contact_info = contact_info;
        });
    }
}

void License::makeproject(account_name owner, const std::string& project_name){
    require_auth(owner);
    for( const auto& project : project_table ) {
        if(project.project_name == project_name && project.owner_name == owner){
            eosio_assert(false, "owner with project already exists" );
            return;
        }
    }
    auto project_itr = project_table.emplace(_self, [&](auto& project){
        project.owner_name = owner;
        project.project_name = project_name;
        auto account_itr = accounts.find(owner);
        if(account_itr == accounts.end()){
            project.company_name = account_itr->company_name;
            project.contact_info = account_itr->contact_info;
            project.status = 0; //初始化未授权，须另购买
        }
    });
}

void License::buylicense(account_name owner, const std::string& project_name){
    require_auth(owner);
    bool bFind = false;

    auto customer_index = project_table.template get_index<N(getowner_name)>();
    account_name customer_acct = eosio::chain::string_to_name(owner);
    auto cust_itr = customer_index.find(customer_acct);
    while (cust_itr != service_table.end() && cust_itr->owner_name == customer_acct) {
        if(cust_itr->project_name == project_name){
            if(cust_itr->status == 0){
                //TODO 判断当前账户余额，购买转账等操作
                project_table.modify(cust_itr, 0, [&](auto& project) {
                    project.status = 1;
                });
            }
            else{
                eosio_assert(false, "The current project is authorized" );
            }
            bFind = true;
            break;
        }
        cust_itr++;
    } 
    eosio_assert(bFind, "owner with project not exists" );
}

void License::testlicense(account_name owner, const std::string& project_name){
    require_auth(owner);
    bool bFind = false;
    for( const auto& project : project_table ) {
        if(project.project_name == project_name && project.owner_name == owner){
            eosio_assert((project.status == 1), "The current project is not authorized" );
            bFind = true;
            break;
        }
    }
    eosio_assert(bFind, "owner with project not exists" );
}