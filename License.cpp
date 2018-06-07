#include <License.hpp>

void License::changeUserInfo(account_name owner, const std::string& company_name, const std::string& contact_info){
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

void License::createProject(account_name owner, const std::string& project_name){
    require_auth(owner);
    for( const auto& project : projects ) {
        if(project.project_name == project_name && project.owner == owner){
            eosio_assert(false, "owner with project already exists" );
            return;
        }
    }
    auto project_itr = projects.emplace(_self, [&](auto& project){
        project.owner = owner;
        project.project_name = project_name;
        auto account_itr = accounts.find(owner);
        if(account_itr == accounts.end()){
            project.company_name = account_itr->company_name;
            project.contact_info = account_itr->contact_info;
        }
    });
}

void License::changeProject(account_name owner, const std::string& project_name, const std::string& company_name, const std::string& contact_info){
    require_auth(owner);
    auto project_itr = projects.find(project_name);
    if(project_itr == projects.end()){
        projects.modify(project_itr, 0, [&](auto& project) {
            project.company_name = company_name;
            project.contact_info = contact_info;
        });
    }
}

void License::buyLicense(account_name owner, const std::string& project_name, uint8_t license_type){
    require_auth(owner);
}

void License::getLicense(account_name owner, const std::string& project_name, uint8_t license_type){
    require_auth(owner);
}