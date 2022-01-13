#ifndef DATA_H
#define DATA_H

#include <libwebsockets.h>
#include "queue_with_id.hpp"
#include <array>
#include <mutex>

struct PerSessionData {
	lws* wsi;
	uint64_t id;
};

template<size_t N>
struct Payload
{
	std::array<uint8_t, N> data{};
	size_t len{};
};

using Buffer = Payload<256>;

template<typename Mutex>
struct PerVHostData {
	QueueWithId<Buffer, Mutex>* send_queue_;

	/**
	 * \brief	Creates a protocol buffers message and adds it to the send queue
	 * \param	buffer Protocol buffers which is suppose to be encoded.
	 * \param	pss_id Client Id that this message will be sent to.
	 */
	void CreateMessage(Buffer buffer, const uint64_t pss_id) const {
		send_queue_->enqueue(pss_id, std::forward<Buffer>(buffer));
	}

	/**
	 * \brief	Writes the message to the wire when it's ready to be written. This function doesn't block.
	 * \param	wsi Web socket instance which is ready to be written on.
	 * \param	pss_id Client Id
	 */
	void SendMessage(lws* wsi, const uint64_t pss_id) const {

		// get the message from the queue
		auto message_opt = send_queue_->dequeue(pss_id);
		if(!message_opt.has_value()) {
			return;
		}

		if(!wsi) {
			lwsl_err("Client has disappeared!\n");
			return;
		}

		auto& message = message_opt.value();

		// write the message to the wire.
		const auto bytes_sent = lws_write(wsi, message.data.data() + LWS_PRE, message.len, LWS_WRITE_BINARY);

		// make sure that the whole message is sent
		if (bytes_sent < static_cast<int>(message.len)) {
			lwsl_err("ERROR %d writing to ws\n", bytes_sent);
		}

		lwsl_debug("Sent %d bytes\n", bytes_sent);
	}
};

#endif // !DATA_H
