#pragma once
/* 
 * File:   UdpOnce.h
 * Author: vfs
 *
 * Created on 29 Сентябрь 2013 г., 1:33
 */

#include "UdpServer.h"

class UdpOnce : public udp_server {
public:
    UdpOnce(boost::asio::io_service& io_service,
            udp::endpoint& listenAddress, string idStr);

    ~UdpOnce();



    void handle_send(boost::shared_ptr<std::string> message,
            const boost::system::error_code& error,
            std::size_t bytes_transferred);

protected:
    virtual void handle_receive(const boost::system::error_code& error,
            std::size_t bytes_transferred);
private:

};



