#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>

// 前向声明
class QueryResult;
class Query_base;

// TextQuery类：读取和处理文件，查询单词在文本中的行号
class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;  // 定义line_no为行号类型
    TextQuery(std::ifstream &);  // 构造函数
    QueryResult query(const std::string &) const;  // 查询函数

private:
    std::shared_ptr<std::vector<std::string>> file;  // 保存输入文件的每一行
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;  // 单词到行号的映射
};

// QueryResult类：保存查询的结果
class QueryResult {
    friend std::ostream &print(std::ostream &, const QueryResult &);

public:
    QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p,
                std::shared_ptr<std::vector<std::string>> f)
        : sought(s), lines(p), file(f) {}

    std::shared_ptr<std::set<TextQuery::line_no>> lines;  // 保存查询到的行号集合
    std::shared_ptr<std::vector<std::string>> file;  // 保存整个文件的内容

private:
    std::string sought;  // 查询的单词
};

// 打印查询结果
std::ostream &print(std::ostream &os, const QueryResult &qr) {
    os << qr.sought << " 出现了 " << qr.lines->size() << " 次\n";
    for (auto num : *qr.lines)
        os << "\t(第 " << num + 1 << " 行) " << (*qr.file)[num] << "\n";
    return os;
}

// Query_base类：所有查询类型的抽象基类
class Query_base {
    friend class Query;

protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;  // 虚析构函数，确保子类正确析构

private:
    virtual QueryResult eval(const TextQuery &) const = 0;  // 纯虚函数，执行查询
    virtual std::string rep() const = 0;  // 返回查询的字符串表示
};

// Query类：接口类，管理Query_base对象
class Query {
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);

public:
    // 构造函数，接受一个单词
    Query(const std::string &);
    QueryResult eval(const TextQuery &t) const { return q->eval(t); }
    std::string rep() const { return q->rep(); }

private:
    Query(std::shared_ptr<Query_base> query) : q(query) {}  // 构造函数，接受一个Query_base的指针
    std::shared_ptr<Query_base> q;  // 指向Query_base派生类对象的智能指针
};

// WordQuery类：执行简单单词查询
class WordQuery : public Query_base {
    friend class Query;

    WordQuery(const std::string &s) : query_word(s) {}

    QueryResult eval(const TextQuery &t) const override { return t.query(query_word); }
    std::string rep() const override { return query_word; }

    std::string query_word;  // 要查询的单词
};

// BinaryQuery类：二元查询的抽象基类，派生出AND和OR查询
class BinaryQuery : public Query_base {
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s)
        : lhs(l), rhs(r), opSym(s) {}

    std::string rep() const override {
        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
    }

    Query lhs, rhs;  // 左右两侧的查询
    std::string opSym;  // 操作符符号（如& 或 |）
};

// AndQuery类：表示 AND 查询
class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &, const Query &);
    AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") {}

    QueryResult eval(const TextQuery &) const override;
};

// OrQuery类：表示 OR 查询
class OrQuery : public BinaryQuery {
    friend Query operator|(const Query &, const Query &);
    OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|") {}

    QueryResult eval(const TextQuery &) const override;
};

// NotQuery类：表示 NOT 查询
class NotQuery : public Query_base {
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q) {}

    std::string rep() const override { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery &) const override;

    Query query;  // 要取反的查询
};

// 操作符重载，用于 AND, OR, NOT 查询
inline Query operator~(const Query &operand) {
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

inline Query operator&(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

inline Query operator|(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

// TextQuery类的构造函数：读取文件并建立单词与行号的映射
TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>) {
    std::string text;
    while (std::getline(is, text)) {
        file->push_back(text);
        int n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while (line >> word) {
            auto &lines = wm[word];
            if (!lines) lines.reset(new std::set<line_no>);
            lines->insert(n);
        }
    }
}

// query方法：返回查询单词的结果
QueryResult TextQuery::query(const std::string &sought) const {
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

// AndQuery的eval方法：返回两个查询结果的交集
QueryResult AndQuery::eval(const TextQuery &text) const {
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>();
    std::set_intersection(left.lines->begin(), left.lines->end(),
                          right.lines->begin(), right.lines->end(),
                          std::inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.file);
}

// OrQuery的eval方法：返回两个查询结果的并集
QueryResult OrQuery::eval(const TextQuery &text) const {
    auto right = rhs.eval(text), left = lhs.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>(left.lines->begin(), left.lines->end());
    ret_lines->insert(right.lines->begin(), right.lines->end());
    return QueryResult(rep(), ret_lines, left.file);
}

// NotQuery的eval方法：返回查询结果的补集
QueryResult NotQuery::eval(const TextQuery &text) const {
    auto result = query.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>();
    auto sz = result.file->size();
    for (size_t n = 0; n != sz; ++n) {
        if (result.lines->find(n) == result.lines->end())
            ret_lines->insert(n);
    }
    return QueryResult(rep(), ret_lines, result.file);
}

// Query类的构造函数实现
Query::Query(const std::string &s) : q(new WordQuery(s)) {}

// 主函数
int main() {
    std::ifstream file("test.txt");  // 替换为你的文件路径
    TextQuery tq(file);

    // Query q = Query("fiery") & Query("bird") | ~Query("wind");
    Query q = Query("apple") & Query("orange"); // 创建一个 AndQuery 查询
    std::cout << q.rep() << std::endl; // 输出查询表达式 "(apple & orange)"
    QueryResult result = q.eval(tq); // 执行查询，返回结果


    // const auto result = q.eval(tq);
    // print(std::cout, result);

    return 0;
}
