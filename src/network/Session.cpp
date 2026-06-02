//
// Created by 신은찬 on 5/18/26.
//
#include "../../include/network/Session.h"

#include "../../include/network/Factory/SocketFactory.h"
#include "../../include/network/protocol/VANProtocol.h"

Session::Session(intptr_t sockfd) {
    socket = SocketFactory::create();
    socket->setHandle(sockfd);
}

void Session::handleRead() {
    int read_byte = Session::read();
    if (read_byte == 0) {
        //abort
    } else if (read_byte == -1) {
        //abort
    }
    PacketParser::ParsingResult parsing_result = packet_parser.parse(socket->read_buffer);
    switch (parsing_result.state) {
        case (PacketParser::WAITING) :
            socket->read_buffer.consume(parsing_result.consumable_bytes);
            break;
        case(PacketParser::NOT_FOUND) :
        case(PacketParser::ABORT):
            socket->read_buffer.consume(parsing_result.consumable_bytes);
            break;
        case(PacketParser::COMPLETE) :
            VANProtocol protocol;
            const uint8_t* p = socket->read_buffer.peek();
            protocol.setData(std::vector(p + parsing_result.stx_pos, p + parsing_result.etx_pos + VANProtocol::ETX_LENGTH - 1));
            //TODO 서비스 핸들러에게 프로토콜 전달
            break;
    }

}

void Session::handleWrite(std::string client_data) {
    int write_byte = write(reinterpret_cast<const uint8_t*>(client_data.data()), client_data.size());
    // abort(); 또는 whole retry;
    int sent_byte = flush();
    if (client_data.size() != sent_byte) {
        // abort(); 또는 whole retry;
    }
}

int Session::read() {
    int len = 0;
    uint8_t tmp[socket->read_buffer.size_limit];
    while (true) {
        int n = socket->read(socket->read_buffer.readableBytes());
        if (n > 0) socket->read_buffer.append(tmp, n);
        else if (n == 0) return 0;
        else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) break;
            return -1;
        }
        len += n;
    }
    return len;
}

int Session::write(const uint8_t* data, std::size_t len) {
    socket->write_buffer.append(data, len);
    //TODO isWriting 같은 상태처리 필요
    return len;
}

int Session::flush() {
    int n = 0;
    while (socket->write_buffer.readableBytes() > 0) {
        int sent = socket->send(socket->write_buffer.peek(), socket->write_buffer.readableBytes());
        if (sent > 0) {
            socket->write_buffer.consume(sent);
            n += sent;
        } else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return 0;
            }
            return -1;
        }
    }
    return n;
}

intptr_t Session::getSockfd() {
    return socket->getHandle();
}

bool Session::checkConeectionAlive() {
    return socket->msgPeek() > 0;
}

