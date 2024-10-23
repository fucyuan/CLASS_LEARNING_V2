

# C++ Primer 第15章学习记录

本项目包含了我在学习 *C++ Primer* 第15章“面向对象程序设计”过程中编写的代码和笔记。以下是项目目录的详细说明，以及各个程序的用途和功能。

## 目录结构

```
├── build
├── doc
└── src
```

### 1. **build**
该文件夹存放了编译后的可执行文件，可以直接运行相应的程序。这些文件都是根据 `src` 目录下的 C++ 源代码编译而成的。

| 文件名 | 说明 |
|--------|------|
| `BookstoreDiscount` | 书籍折扣系统的初版 |
| `BookstoreDiscount V2` | 书籍折扣系统第二版 |
| `BookstoreDiscount V2 copy` | 书籍折扣系统第二版的副本 |
| `DefaultArgsInheritanceDemo` | 展示如何在继承中使用默认参数 |
| `DerivedInheritanceConstructorDemo` | 子类继承构造函数的演示 |
| `discount_system.exe` | 折扣系统的完整实现 |
| `friend_class_access_control.exe` | 展示友元类和访问控制 |
| `inheritance_access_control.exe` | 继承中的访问控制演示 |
| `inheritance_access_restrictions.exe` | 继承访问限制的演示 |
| `inheritance_assignment_check.exe` | 继承赋值操作检查 |
| `inheritance_scope_lookup.exe` | 继承作用域查找的演示 |
| `member_hiding_in_inheritance.exe` | 成员隐藏在继承中的行为 |
| `QueryProgram` | 文本查询系统 |
| `QuoteCloneSystem` | 折扣书籍查询系统 |
| `QuotePricingCalculator` | 书籍定价计算系统 |
| `RecursiveIssueDemo` | 递归问题的演示 |
| `shape_inheritance_system.exe` | 形状类继承系统 |
| `VirtualDestructorDemo` | 虚析构函数演示 |

### 2. **doc**
该目录存放了学习过程中的笔记和练习解答。

| 文件名 | 说明 |
|--------|------|
| `练习解答.md` | 书中练习的解答，Markdown 格式 |
| `练习解答.pdf` | 书中练习的解答，PDF 格式 |

### 3. **src**
该目录包含所有的 C++ 源代码。每个文件对应一个具体的学习主题或示例代码。

| 文件名 | 说明 |
|--------|------|
| `access_control_inheritance.cpp` | 演示访问控制和继承的示例 |
| `BookstoreDiscount.cpp` | 书店折扣系统初版的实现 |
| `BookstoreDiscount V2.cpp` | 书店折扣系统的改进版 |
| `BookstoreDiscount V3.cpp` | 书店折扣系统的第三版 |
| `DefaultArgsInheritanceDemo.cpp` | 展示如何在继承中使用默认参数的示例 |
| `DerivedInheritanceConstructorDemo.cpp` | 子类构造函数继承的示例 |
| `discount_system.cpp` | 完整的折扣系统实现 |
| `friend_class_access_control.cpp` | 演示友元类与访问控制的代码 |
| `inheritance_access_control.cpp` | 继承中的访问控制示例 |
| `inheritance_access_restrictions.cpp` | 演示继承中的访问限制 |
| `inheritance_assignment_check.cpp` | 演示继承赋值操作的代码 |
| `inheritance_scope_lookup.cpp` | 继承作用域查找示例 |
| `member_hiding_in_inheritance.cpp` | 演示继承中成员隐藏的代码 |
| `QueryProgram.cpp` | 一个文本查询系统的实现 |
| `QuoteCloneSystem.cpp` | 书籍折扣系统中的克隆机制示例 |
| `QuotePricingCalculator.cpp` | 实现书籍定价计算系统 |
| `RecursiveIssueDemo.cpp` | 演示递归问题的代码 |
| `shape_inheritance_system.cpp` | 演示形状类继承的代码 |
| `test.cpp` | 测试文件 |
| `VirtualDestructorDemo.cpp` | 虚析构函数的演示代码 |

## 编译与运行

### 编译方法
可以使用 `g++` 编译每个 C++ 源代码文件，例如：
```bash
g++ -std=c++11 src/BookstoreDiscount.cpp -o build/BookstoreDiscount
```

### 运行方法
在终端运行可执行文件，例如：
```bash
./build/BookstoreDiscount
```

## 项目主题

本项目主要涉及以下几个C++面向对象编程的关键主题：

- **继承与派生**：包括访问控制、构造函数继承、成员隐藏等内容。
- **虚函数与多态**：展示了如何使用虚函数来实现多态机制。
- **友元类与访问控制**：通过友元类访问类的私有成员。
- **默认参数与继承**：演示如何在继承中使用默认参数。
- **Query查询系统**：一个完整的文本查询系统，结合了面向对象和动态绑定的概念。
- **折扣系统**：用于计算书籍折扣的系统，展示了类的继承和多态的应用。

