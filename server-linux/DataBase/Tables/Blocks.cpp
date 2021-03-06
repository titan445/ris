#include "Blocks.h"

namespace Database {
    namespace Tables {

        Blocks::Blocks(Connection* conn) : TABLE_NAME("`blocks`") {
            this->conn = conn;
        }

        ResultSet* Blocks::freeSpaceBlock(uint32_t fileSize) {
            ResultSet* res;
            sql::PreparedStatement* prep_stmt;

            prep_stmt = conn-> prepareStatement("SELECT * FROM " + TABLE_NAME
                    + " WHERE `occupied_space` <= ?");
            prep_stmt->setUInt(1, fileSize);
            res = prep_stmt->executeQuery();

            delete prep_stmt;
            return res;
        }

        //@todo: refractoring

        uint32_t Blocks::insertBlocks(std::string path, uint32_t occuredSpace, std::string ip) {
            sql::PreparedStatement* prep_stmt;
 BOOST_LOG_TRIVIAL(debug) << "Block : insert= ";
            uint32_t idInsertLast = -1;
            ResultSet* res;
            prep_stmt = conn->prepareStatement("select `cloudsris`.`insertNewBlock`(?,?,?)");
            prep_stmt->setString(1, path);
            prep_stmt->setUInt(2, occuredSpace);
            prep_stmt->setString(3, ip);
            res = prep_stmt->executeQuery();
            res->next();
            idInsertLast = res->getUInt(1);
BOOST_LOG_TRIVIAL(debug) << "Block : end insert= ";
            delete prep_stmt, res;
            return idInsertLast;
        }

        bool Blocks::deleteRecords(std::string path) {
            sql::PreparedStatement* prep_stmt;
            bool result = false;

            prep_stmt = conn->prepareStatement("DELETE FROM " +
                    TABLE_NAME + " WHERE `address` = ?");
            prep_stmt->setString(1, path);
            result = prep_stmt->executeUpdate() > 0;

            delete prep_stmt;
            return result;
        }

        bool Blocks::deleteRecords(uint32_t id) {
            sql::PreparedStatement* prep_stmt;
            bool result = false;

            prep_stmt = conn->prepareStatement("DELETE FROM " +
                    TABLE_NAME + " WHERE `id` = ?");
            prep_stmt->setUInt(1, id);
            result = prep_stmt->executeUpdate() > 0;

            delete prep_stmt;
            return result;
        }

        bool Blocks::updateOccuredSize(unsigned int id, uint32_t occured) {
            sql::PreparedStatement* prep_stmt;
            bool result = false;

            prep_stmt = conn->prepareStatement("UPDATE " +
                    TABLE_NAME + " SET `occupied_space` = ? WHERE `id` = ?");
            prep_stmt->setUInt(1, occured);
            prep_stmt->setUInt(2, id);
            result = prep_stmt->executeUpdate() > 0;

            delete prep_stmt;
            return result;
        }

        bool Blocks::updateOccuredSize(std::string path, uint32_t occured) {
            sql::PreparedStatement* prep_stmt;
            bool result = false;
BOOST_LOG_TRIVIAL(debug) << "Block : start updateOccuredSize= ";
            prep_stmt = conn->prepareStatement("UPDATE " +
                    TABLE_NAME + " SET `occupied_space` = ? WHERE `address` = ?");
            prep_stmt->setUInt(1, occured);
            prep_stmt->setString(2, path);
            result = prep_stmt->executeUpdate() > 0;
BOOST_LOG_TRIVIAL(debug) << "Block : end updateOccuredSize= ";
            delete prep_stmt;
            return result;
        }
        
        std::string Blocks::GetPathToBlockByBlockId(uint32_t block_id){
            sql::PreparedStatement* prep_stmt;
BOOST_LOG_TRIVIAL(debug) << "Block : start GetPathToBlockByBlockId= ";
            std::string path = "";
            ResultSet* res;
            prep_stmt = conn->prepareStatement("select address FROM "+ TABLE_NAME +
                    " where id =?");
            
            prep_stmt->setUInt(1, block_id);
           
            res = prep_stmt->executeQuery();
            res->next();
            path = res->getString(1);
BOOST_LOG_TRIVIAL(debug) << "Block : stop GetPathToBlockByBlockId= ";
            delete prep_stmt, res;
            return path;
        }

        
        uint32_t Blocks::GetIdByPathToBlock(std::string path){
            sql::PreparedStatement* prep_stmt;
BOOST_LOG_TRIVIAL(debug) << "Block : start GetPathToBlockByBlockId= ";
            uint32_t id =0;
            ResultSet* res;
            prep_stmt = conn->prepareStatement("select id FROM "+ TABLE_NAME +
                    " where `address` = ?;");
            
            prep_stmt->setString(1, path);
           
            res = prep_stmt->executeQuery();
            res->next();
            id = res->getUInt(1);
BOOST_LOG_TRIVIAL(debug) << "Block : stop GetPathToBlockByBlockId= ";
            delete prep_stmt, res;
            return id;
        }
        Blocks::~Blocks() {

        }

    }
}