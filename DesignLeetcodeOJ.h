#ifndef _DESIGN_LEETCODE_OJ_H
#define _DESIGN_LEETCODE_OJ_H
#include "Debug.h"
#include <mutex>
#include <memory>
/*
Amazon

1. Identify enum
2. Identify class hierarchy, virtual methods, singleton, factory method
3. Identify relationships/mappings
4. Identify interactions
 */
namespace DesignLeetcodeOJ
{
    enum ProgLangType
    {
        CppT,
        JavaT,
        PythonT,
    };
    enum RDBMSType
    {
        MySqlT,
        MSSQLServerT,
        OracleT,
    };
    enum CompilerType
    {
        ProgLangCompilerT,
        RDBMST,
    };
    struct Status
    {
        Status(){}
    };
    //1. compiler hierarchy
    class CompilerBase
    {
        CompilerType m_type;
    public:
        CompilerBase(CompilerType t = ProgLangCompilerT):m_type(t){}
        CompilerType GetCompierType() const {return m_type;}
        virtual Status CompileAndRun(const std::string & program) = 0;
        virtual ~CompilerBase() = 0;
    };
    CompilerBase::~CompilerBase() {}
    class ProgLangCompiler : public CompilerBase
    {
        ProgLangType m_progLangType;
    public:
        ProgLangCompiler(ProgLangType t = CppT):CompilerBase(ProgLangCompilerT),m_progLangType(t){}
        ProgLangType GetProgLangType() const {return m_progLangType;}
        static ProgLangCompiler * NewProgLangCompiler(ProgLangType t);//factory method
        virtual ~ProgLangCompiler() = 0;
    };
    ProgLangCompiler::~ProgLangCompiler() {}
    class Cpp : public ProgLangCompiler
    {
    public:
        Cpp():ProgLangCompiler(CppT){}
        Status CompileAndRun(const std::string & program)
        {
            return Status();
        }
        ~Cpp(){}
    };
    class Java : public ProgLangCompiler
    {
    public:
        Java():ProgLangCompiler(JavaT){}
        Status CompileAndRun(const std::string & program)
        {
            return Status();
        }
        ~Java(){}
    };
    class Python : public ProgLangCompiler
    {
    public:
        Python():ProgLangCompiler(PythonT){}
        Status CompileAndRun(const std::string & program)
        {
            return Status();
        }
        ~Python(){}
    };
    ProgLangCompiler * ProgLangCompiler::NewProgLangCompiler(ProgLangType t)
    {
        switch (t)
        {
            case CppT: return new Cpp;
            case JavaT: return new Java;
            case PythonT: return new Python;
            default: return new Cpp;
        }
    }
    class RDBMS : public CompilerBase
    {
        RDBMSType m_rdbmsType;
    public:
        RDBMS(RDBMSType t = MySqlT):CompilerBase(RDBMST),m_rdbmsType(t){}
        RDBMSType GetRDBMSType() const {return m_rdbmsType;}
        static RDBMS * NewRDBMS(RDBMSType t);//factory method
        virtual ~RDBMS() = 0;
    };
    RDBMS::~RDBMS(){}
    class MySql : public RDBMS
    {
    public:
        MySql():RDBMS(MySqlT){}
        Status CompileAndRun(const std::string & program)
        {
            return Status();
        }
        ~MySql(){}
    };
    class MSSQLServer : public RDBMS
    {
    public:
        MSSQLServer():RDBMS(MSSQLServerT){}
        Status CompileAndRun(const std::string & program)
        {
            return Status();
        }
        ~MSSQLServer(){}
    };
    class Oracle : public RDBMS
    {
    public:
        Oracle():RDBMS(OracleT){}
        Status CompileAndRun(const std::string & program)
        {
            return Status();
        }
        ~Oracle(){}
    };
    RDBMS * RDBMS::NewRDBMS(RDBMSType t)
    {
        switch(t)
        {
            case MySqlT: return new MySql;
            case MSSQLServerT: return new MSSQLServer;
            case OracleT: return new Oracle;
            default: return new MySql;
        }
    }
    enum QuestionType
    {
        AlgoQuestionT,
        RDBQuestionT,
    };
    enum AlgoQuestionType
    {
        TwoSumT,
        ThreeSumT,
    };
    enum RDBQuestionType
    {
        CombineTwoTablesT,
    };
    //2. question hierarchy
    class QuestionBase
    {
        QuestionType m_type;
    public:
        QuestionBase(QuestionType t = AlgoQuestionT):m_type(t){}
        QuestionType GetType() const {return m_type;}
        //Status Submit() = 0;
        virtual ~QuestionBase() = 0;
    };
    QuestionBase::~QuestionBase() {}
    class Algorithm : public QuestionBase
    {
        AlgoQuestionType m_algoType;
    public:
        Algorithm(AlgoQuestionType t = TwoSumT):QuestionBase(AlgoQuestionT),m_algoType(t){}
        AlgoQuestionType GetAlgoQuestionType() const {return m_algoType;}
        static Algorithm * NewAlgorithm(AlgoQuestionType t);//factory method
        virtual ~Algorithm() = 0;
    };
    Algorithm::~Algorithm() {}
    class TwoSum : public Algorithm
    {
        std::vector<std::vector<int>> m_testCases;
    public:
        TwoSum():Algorithm(TwoSumT){}
        ~TwoSum(){}
    };
    class ThreeSum : public Algorithm
    {
        std::vector<std::vector<int>> m_testCases;
    public:
        ThreeSum():Algorithm(ThreeSumT){}
        ~ThreeSum(){}
    };
    Algorithm * Algorithm::NewAlgorithm(AlgoQuestionType t)
    {
        switch(t)
        {
            case TwoSumT: return new TwoSum;
            case ThreeSumT: return new ThreeSum;
            default: return new TwoSum;
        }
    }
    class RelationalDatabase : public QuestionBase
    {
        RDBQuestionType m_rdbType;
    public:
        RelationalDatabase(RDBQuestionType t = CombineTwoTablesT):QuestionBase(RDBQuestionT),m_rdbType(t){}
        RDBQuestionType GetRDBQuestionType() const {return m_rdbType;}
        static RelationalDatabase * NewRelationalDatabase(RDBQuestionType t);
        virtual ~RelationalDatabase() = 0;
    };
    RelationalDatabase::~RelationalDatabase() {}
    class CombineTwoTables : public RelationalDatabase
    {
    public:
        CombineTwoTables(){}
        ~CombineTwoTables(){}
    };
    RelationalDatabase * RelationalDatabase::NewRelationalDatabase(RDBQuestionType t)
    {
        switch (t)
        {
            case CombineTwoTablesT: return new CombineTwoTables;
            default: return new CombineTwoTables;
        }
    }

    class User
    {
    public:
        User(){}
        ~User(){}
    };

    class OJSingleton
    {
        /*===============Singleton==============*/
        static std::unique_ptr<OJSingleton> m_instance;
        static std::once_flag m_flag;
        OJSingleton(const OJSingleton &) = delete;
        OJSingleton & operator=(const OJSingleton &) = delete;
    public:
        static OJSingleton & Instance()
        {
            std::call_once(m_flag, []
            {
                m_instance.reset(new OJSingleton);
            });
            return *m_instance.get();
        }
        /*===============Singleton==============*/
    private:
        OJSingleton()
        {
            std::cout << "ctor" << std::endl;
        }
    public:
        ~OJSingleton()
        {

        }
        void Print()
        {
            std::cout << "hello" << std::endl;
        }
    };
    std::unique_ptr<OJSingleton> OJSingleton::m_instance;
    std::once_flag OJSingleton::m_flag;


}
#endif
