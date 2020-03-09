#ifndef _DESIGN_PATTERN_INTERPRETER_H
#define _DESIGN_PATTERN_INTERPRETER_H
#include "Debug.h"
namespace DesignPattern_Interpreter
{
    class Expression
    {
    public:
        Expression(){}
        virtual bool interpret(const std::string & context) = 0;
    };
    class TerminalExpression : public Expression
    {
        std::string m_data;
    public:
        TerminalExpression(const std::string & data):m_data(data)
        {

        }
        bool interpret(const std::string & context) override
        {
            if (context.find(m_data) != std::string::npos)
                return true;
            return false;
        }
    };
    class OrExpression : public Expression
    {
        Expression * m_expr1;
        Expression * m_expr2;
    public:
        OrExpression(Expression * expr1, Expression * expr2):m_expr1(expr1), m_expr2(expr2)
        {

        }
        bool interpret(const std::string & context) override
        {
            return m_expr1->interpret(context) || m_expr2->interpret(context);
        }
    };
    class AndExpression : public Expression
    {
        Expression * m_expr1;
        Expression * m_expr2;
    public:
        AndExpression(Expression * expr1, Expression * expr2): m_expr1(expr1), m_expr2(expr2)
        {

        }
        bool interpret(const std::string & context) override
        {
            return m_expr1->interpret(context) && m_expr2->interpret(context);
        }
    };

    Expression * GetMaleExpression()
    {
        //Rule: Robert and John are male
        Expression * robert = new TerminalExpression("Robert");
        Expression * john = new TerminalExpression("John");
        return new OrExpression(robert, john);
    }
    Expression * GetMarriedWomanExpression()
    {
        //Rule: Julie is a married women
        Expression * julie = new TerminalExpression("Julie");
        Expression * married = new TerminalExpression("Married");
        return new AndExpression(julie, married);
    }

    void Test()
    {
        Expression * isMale = GetMaleExpression();
        Expression * isMarriedWoman = GetMarriedWomanExpression();
        std::cout << "John is male? " << isMale->interpret("John") << std::endl;
        std::cout << "Julie is a married women? " << isMarriedWoman->interpret("Married Julie") << std::endl;
    }
}
#endif
