#include <iostream>
#include <stack>
#include <string>
#include <vector>

int isHigher(char c1, char c2) {
  if ((c1 == '*' || c1 == '/') && (c2 == '+' || c2 == '-'))
    return 1;
  else if ((c2 == '*' || c2 == '/') && (c1 == '+' || c1 == '-'))
    return -1;
  else
    return 0;
}

/**
 * 将输入的中缀表达式转化为后缀表达式
 * @param nifixStr 中缀表达式
 * @return 字符串数组，每一个字符串代表一个数字或者运算符
 */
std::vector<std::string> NifixToPostfix(std::string& nifixStr) {
  std::stack<char> operatorSc;
  std::vector<std::string> ans;
  int temp = 0;
  for (int i = 0; i < nifixStr.size(); ++i) {
    char a = nifixStr[i];
    if (a == '+' || a == '-' || a == '/' || a == '*') {
      while (!operatorSc.empty()) {
        char peek = operatorSc.top();
        if (isHigher(peek, a) == -1 || peek == '(') break;
        operatorSc.pop();
        ans.push_back(std::string(1, peek));
      }
      operatorSc.push(a);
    } else if (a == '(' || a == ')') {
      if (a == ')') {
        while (!operatorSc.empty()) {
          char peek = operatorSc.top();
          operatorSc.pop();
          if (peek == '(') break;
          ans.push_back(std::string(1, peek));
        }
        continue;
      }
      operatorSc.push(a);
    } else if (a >= '0' && a <= '9') {
      int cur = i;
      std::string curStr = "";
      for (; cur < nifixStr.size(); ++cur) {
        char b = nifixStr[cur];
        if (b >= '0' && b <= '9')
          curStr += b;
        else
          break;
      }
      i = cur - 1;
      ans.push_back(std::move(curStr));
    } else if (a == ' ' || a == '\t') {
      continue;
    } else {
      throw "unvalid";
    }
  }

  while (!operatorSc.empty()) {
    char peek = operatorSc.top();
    if (peek == '(') throw "unvalid";
    operatorSc.pop();
    ans.push_back(std::string(1, peek));
  }
  return ans;
}

/**
 * 计算后缀表达式
 */
int PostfixCal(std::vector<std::string>& strs) {
  std::stack<int> sc;
  for (int i = 0; i < strs.size(); ++i) {
    std::string& str = strs[i];
    if (str.compare("+") == 0 || str.compare("-") == 0 ||
        str.compare("/") == 0 || str.compare("*") == 0) {
      if (sc.size() < 2) throw "unvalid";
      int b = sc.top();
      sc.pop();
      int a = sc.top();
      sc.pop();
      if (str.compare("+") == 0)
        sc.push(a + b);
      else if (str.compare("-") == 0)
        sc.push(a - b);
      else if (str.compare("/") == 0)
        sc.push(a / b);
      else
        sc.push(a * b);
    } else {
      int temp = 0;
      for (int k = 0; k < str.size(); ++k) temp = temp * 10 + int(str[k] - '0');
      sc.push(temp);
    }
  }

  return sc.top();
}

/**
 * 使用方式
 */
int main() {
  std::string s = "(200 + 80) * 2 - 123 + 99 / 3";
  std::vector<std::string> ans = NifixToPostfix(s);
  for (int i = 0; i < ans.size(); ++i) std::cout << ans[i] << " ";
  std::cout << std::endl;
  int h = PostfixCal(ans);
  std::cout << h << std::endl;
  return 0;
}