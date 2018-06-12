#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

class License : public eosio::contract {
    public:
        License( account_name self )
        :eosio::contract(self)
        ,accounts(_self, _self)
        ,projecttable(_self, _self){}

        void setuserinfo(account_name owner, const std::string& company_name, const std::string& contact_info);
        void makeproject(account_name owner, const std::string& project_name);
        void buylicense(account_name owner, const std::string& project_name);
        void testlicense(account_name owner, const std::string& project_name);

    private:
        //@abi table accounts i64
        struct account{
            account_name name;
            std::string company_name;
            std::string contact_info;
            uint8_t level;
            uint64_t primary_key()const { return name; }
            EOSLIB_SERIALIZE(account, (name)(company_name)(contact_info)(level))
        };

        typedef eosio::multi_index<N(accounts),account> account_table;
        account_table accounts;

        //@abi table projecttable i64
        struct project{
            uint32_t pkey;
            account_name owner_name;
            std::string project_name;
            std::string company_name;
            std::string contact_info;
            uint8_t      status;

            uint64_t primary_key()const { return pkey; }
            uint64_t getowner_name() const{return owner_name;}
            EOSLIB_SERIALIZE(project, (pkey)(owner_name)(project_name)(company_name)(contact_info)(status))
        };
        //contracts/eosiolib/multi_index.hpp
        //multi_index用于封装智能合约对数据库的管理，增、删、改、查
        //eosio::multi_index<N(表名),数据类型> 
        //一个multi_index最多支持16个二级索引
        //定义二级索引使用eosio::indexed_by模板。N(byowner_name)为索引的名称
        //project表数据类型，uint64_t索引类型即索引函数返回的类型(只支持uint64_t,uint128_t,double,long double,key256类型)，&project::getowner_name索引函数。
        typedef eosio::multi_index<N(projecttable),project, eosio::indexed_by<N(byowner_name), eosio::const_mem_fun<project, account_name, &project::getowner_name> >> projecttable_type;
        projecttable_type projecttable;
};
EOSIO_ABI(License, (setuserinfo)(makeproject)(buylicense)(testlicense))