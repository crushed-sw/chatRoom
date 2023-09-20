#include "../../include/mysql/MySql.hpp"

using namespace crushed::mysql;

MySql::MySql(const std::string& url, const std::string& user, const std::string& password) : MySql(url, user, password, "") {}

MySql::MySql(const std::string& url, const std::string& user, const std::string& password, const std::string& table)
        : url_(url), user_(user), password_(password), table_(table) {
    connect();
}

void MySql::connect() {
    driver_ = sql::mysql::get_driver_instance();
    conn_.reset(driver_->connect(url_, user_, password_));
}

void MySql::setTable(const std::string& table) {
    table_ = table;
}

void MySql::setDatabse(const std::string& database) {
    database_ = database;
    conn_->setSchema(database);
}

MySql& MySql::query(const std::string& str) {
    std::unique_lock<std::mutex> locker(mutex_);
    if(!conn_)
        connect();

    pstmt_.reset(conn_->prepareStatement(str));
    return *this;
}

MySql& MySql::update(const std::string& str) {
    return query(str);
}

MySql& MySql::bind(const std::vector<std::string>& para) {
    std::unique_lock<std::mutex> locker(mutex_);
    for(int i = 0; i != para.size(); ++i) {
        if(para[i] == "crushed-int-null") {
            pstmt_->setNull(i + 1, sql::DataType::INTEGER);
        } else if(para[i] == "crushed-string-null") {
            pstmt_->setNull(i + 1, sql::DataType::VARCHAR);
        } else {
            pstmt_->setString(i + 1, para[i]);
        }
    }
    return *this;
}

sql::ResultSet* MySql::executeQuery() {
    std::unique_lock<std::mutex> locker(mutex_);
    return pstmt_->executeQuery();
}

void MySql::executeUpdate() {
    std::unique_lock<std::mutex> locker(mutex_);
    pstmt_->executeUpdate();
}
