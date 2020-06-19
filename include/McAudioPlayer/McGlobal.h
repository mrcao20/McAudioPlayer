#pragma once

#include <QEvent>
#include <QVariant>

#include "McMacroDefines.h"

namespace Mc {
template<typename Container>
bool isContains(int index, Container container) {
	if (index >= 0 && index < container.size())
		return true;
	return false;
}
}

class McCustomEvent : public QEvent {
public:
    McCustomEvent(int type, const QVariant &data) noexcept
        : QEvent(static_cast<QEvent::Type>(type))
        , m_data(data)
    {}
    ~McCustomEvent() noexcept;
    
    QVariant data() const noexcept {
        return m_data;
    }
    void setData(const QVariant &val) noexcept {
        m_data = val;
    }
    
private:
    QVariant m_data;
};
