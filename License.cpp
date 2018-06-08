#include <License.hpp>

void License::setuserinfo(account_name owner, const std::string& company_name, const std::string& contact_info){
    
}

void License::makeproject(account_name owner, const std::string& project_name){

}

void License::setproject(account_name owner, const std::string& project_name, const std::string& company_name, const std::string& contact_info){
    require_auth(owner);
    /*auto project_itr = projects.find(project_name);
    if(project_itr == projects.end()){
        projects.modify(project_itr, 0, [&](auto& project) {
            project.company_name = company_name;
            project.contact_info = contact_info;
        });
    }*/
}

void License::buylicense(account_name owner, const std::string& project_name, uint8_t license_type){
    require_auth(owner);
}

void License::getlicense(account_name owner, const std::string& project_name, uint8_t license_type){
    require_auth(owner);
}