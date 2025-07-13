# GraceFt 使用技巧

## 信号-槽机制

在 GraceFt 中，信号-槽机制是一种常用的编程模式，简单地来说，就是当某个事件发生时，触发信号，并调用所有与该信号绑定的槽函数，并且可以传递参数。下面是一个简单的示例，用于演示信号-槽机制的基本用法：
```cpp
GFt::Signal<int> s1;
s1.connect([](int x){
    std::cout << "Received signal with value " << x << std::endl;
    });
s1(10); // 触发信号，并传递参数 10
```
同时，GraceFt 中`GFt::Signal<Args>`的实现是同步调用并且是线程安全的，也就是说，多个线程可以同时绑定槽函数、解除绑定槽函数、触发信号，而不会导致数据竞争或崩溃，但需要注意的是，`GFt::Signal<Args>`只保证与槽函数修改相关的操作是线程安全的，不保证槽函数调用的线程安全，因而如果槽函数内部使用了可能导致数据竞争的操作，则需要开发者手动添加锁保护。
其次，槽函数被调用时，允许在槽函数中移除自己，只要槽函数中可以获取到自己关联的信号槽ID(ssid, Signal-Slot ID)，这可以用于实现某些功能，比如需要在达成某些条件时断开信号槽的连接，例如部件库中滑条和滚动条的实现就利用了这一特性。

## 零阻塞操作

当你需要执行一些较高耗时的操作时，例如文件的IO操作，如果将它们也直接放在主线程逻辑中，会影响事件循环的执行而造成卡顿，此时便需要引入零阻塞操作以避免卡顿的问题。零阻塞操作本质上是异步操作，将高耗时的操作放在不同于主线程的另一线程进行，并在操作完成后通过回调函数通知主线程，这样主线程就可以继续处理其他事件。GraceFt 中并未提供这种操作的直接支持，但可以通过`GFt::PlanEvent`来间接地实现这种操作。要实现它，需要借助于C++标准库中的`std::async`和`std::future`，具体的实现方法如下：
```cpp
std::future<void> f;

std::cout << "Async operation started" << std::endl;
f = std::async(std::launch::async, Async);
PlanEvent::add([&]()->bool {
    std::cout << "PlanEvent Callback Function triggered" << std::endl;
    if (f.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready)
        return true;
    return false;
    },
    [&] {
        std::cout << "Async operation finished" << std::endl;
        std::cout << "Duration: " << duration.count() << "us" << std::endl;
    });
```
通过`std::async`启动一个异步任务，然后将它添加到`GFt::PlanEvent`的条件触发事件中，事件循环会进行轮询，当`std::future`求值结束时，触发回调函数进行后续处理。上面的代码只是一个简单的示例，对于更加复杂的操作，可以将它封装为一个类以便于使用和管理。