#pragma once

class MyClass {
  public:
    MyClass(i32);

    i32 get_my_number();

  private:
    i32 m_my_number{0};
};