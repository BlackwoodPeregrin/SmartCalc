#pragma once

#include <cmath>
#include <string>

#include "../conteiners_SQ/s21_queue.h"
#include "../conteiners_SQ/s21_stack.h"

namespace s21_SmartCalc {
class ModelCalc {
 private:
  enum {
    NUMBER,
    SIGN,
    UNARY_SIGN,
    FUNC,
    X,
  };

 private:
  class Lexem {
   private:
    int _typeElement;
    double _valueElement;

   public:
    /*--constructors--*/
    Lexem(const int &typeElement, const double &valueElement)
        : _typeElement(typeElement), _valueElement(valueElement) {}
    explicit Lexem(int &&typeElement = int(), double &&valueElement = double())
        : _typeElement(typeElement), _valueElement(valueElement) {}
    Lexem(const Lexem &lexem) { *this = lexem; }
    /*--overload operators--*/
    Lexem &operator=(const Lexem &lexem) {
      _typeElement = lexem._typeElement;
      _valueElement = lexem._valueElement;
      return *this;
    }
    /*--mutators--*/
    void setTypeLexem(const int &typeElement) { _typeElement = typeElement; }
    void setTypeLexem(int &&typeElement) { _typeElement = typeElement; }
    void setValueLexem(const double &valueElement) {
      _valueElement = valueElement;
    }
    void setValueLexem(double &&valueElement) { _valueElement = valueElement; }
    /*--lookup--*/
    bool isNumber() { return _typeElement == NUMBER; }
    bool isSign() { return _typeElement == SIGN; }
    bool isUnarySign() { return _typeElement == UNARY_SIGN; }
    bool isFunc() { return _typeElement == FUNC; }
    bool isX() { return _typeElement == X; }
    /*--ascesource--*/
    double getValueLexem() const { return _valueElement; }
  };

 private:
  enum {
    SIN = 0,
    COS = 4,
    TAN = 8,
    ACOS = 12,
    ASIN = 17,
    ATAN = 22,
    SQRT = 27,
    LN = 32,
    LOG = 35,
  };

  enum {
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD,
    POW,
    LEFT_BRECKET,
    RIGHT_BRECKET,
  };

 private:
  s21::Stack<Lexem> _stackResult;
  s21::Queue<Lexem> _queuePolish;
  std::string _strInput;
  std::pair<double, std::string> resultCalc;

 public:
  /*--constructors--*/
  ModelCalc() {}
  ~ModelCalc() { _Clear(); }

  /*--get result--*/
  void installPolishNot(const std::string &strInput);
  std::pair<double, std::string> getResultCalc(const std::string &strInput);
  std::pair<double, std::string> getResultCalcWith_X(const double &x_value);

 private:
  void _SmartCalc(const std::string &strInput);
  void _SmartCalcWith_X(const double &x_value);

 private:
  /*--ModuleCalc methots--*/
  void _Clear();

  void _Polish_natation();
  void _IsNumber(size_t &index_str);
  void _IsFunc(size_t &index_str);
  void _IsSignStackEmpty(const size_t &index_str, const std::string &signs);
  void _IsSign(const size_t &index_str, const std::string &signs);

  void _Calc_result(double x_value = 0.0);
  void _CalcSign(const Lexem &lexem);
  void _CalcUnarySign(const Lexem &lexem);
  void _CalcFunc(const Lexem &lexem);
};
}  // namespace s21_SmartCalc
