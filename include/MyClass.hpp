#pragma once

class MyClass {
  public:
    MyClass(u32);

    u32 get_my_number();

  private:
    u32 m_my_number{0};
};