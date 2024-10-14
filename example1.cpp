//
// Created by kimwoodle on 10/9/24.
//

#include <webdriverxx/webdriverxx.h>
using namespace webdriverxx;

int main() {
    WebDriver firefox = Start(Firefox());
    firefox
            .Navigate("http://google.com")
            .FindElement(ByCss("input[name=q]"))
            .SendKeys("Hello, world!")
            .Submit();
    return 0;
}
