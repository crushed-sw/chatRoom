#ifndef __NON_COPYABLE_HPP
#define __NON_COPYABLE_HPP

namespace crushed {
namespace net {

class NonCopyable {
public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;

protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};

} // namespace net
} // namespace crushed

#endif //__NON_COPYABLE_HPP
