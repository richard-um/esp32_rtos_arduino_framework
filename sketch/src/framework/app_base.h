#pragma once

class app_base
{
public:
  virtual ~app_base() = default;

  void run();

protected:
  virtual void main() = 0;
};
