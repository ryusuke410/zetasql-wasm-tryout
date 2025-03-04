#ifndef EXT_LIB_COUNTER_H_
#define EXT_LIB_COUNTER_H_

namespace ext_lib {

class Counter {
public:
    Counter(int initial);
    void increment();
    int getCount() const;

private:
    int count;
};

} // namespace ext_lib

#endif // EXT_LIB_COUNTER_H_
