#ifndef _MC_REST_RESPONSE_H_
#define _MC_REST_RESPONSE_H_

#include <qstring.h>

template<typename T>
class McRestResponse {
public:
	using type = T;

public:
	McRestResponse(bool success, const QString &msg, const T &payload)
		: McRestResponse(success, msg)
	{
		m_payload = payload;
	}

	McRestResponse(bool success, const QString &msg)
		: m_success(success)
		, m_msg(msg)
	{}

	McRestResponse(const T &payload)
		: McRestResponse(true, "", payload)
	{}

	static McRestResponse ok(const T &payload) noexcept {
		return McRestResponse(payload);
	}

	static McRestResponse fail(const QString &msg) noexcept {
		return McRestResponse(false, msg);
	}

private:
	bool m_success;		// ��־�����Ƿ�ɹ�
	QString m_msg;		// ��Ӧ����ʾ��Ϣ
	T m_payload;		// ��Ӧ������

private:
	friend class McJsonUtils;
};

#endif // !_MC_REST_RESPONSE_H_