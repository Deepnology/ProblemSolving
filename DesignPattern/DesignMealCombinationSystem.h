#ifndef _DESIGN_MEAL_COMBINATION_SYSTEM_H
#define _DESIGN_MEAL_COMBINATION_SYSTEM_H
#include "Debug.h"
/*
Amazon
 */
namespace DesignMealCombinationSystem
{
    enum FoodType
    {
        ProteinT = 0,
        VegeT = 1,
        SideT = 2,
    };
    enum ProteinType
    {
        ChickenT = 0,
        PorkT = 1,
        BeefT = 2,
    };
    enum VegeType
    {
        LettuceT = 0,
        BroccoliT = 1,
    };
    enum SideType
    {
        FriesT = 0,
        SaladT = 1,
        SoupT = 2,
    };
    class FoodBase
    {
        enum FoodType m_type;
    public:
        FoodBase(FoodType t = ProteinT):m_type(t){}
        FoodType GetFoodType() const {return m_type;}
        virtual ~FoodBase() = 0;
    };
    FoodBase::~FoodBase(){}
    class Protein : public FoodBase
    {
        ProteinType m_proteinType;
    public:
        Protein(ProteinType t = ChickenT):FoodBase(ProteinT),m_proteinType(t){}
        ProteinType GetProteinType() const {return m_proteinType;}
        virtual ~Protein() = 0;
        static Protein * NewProtein(ProteinType t);
    };
    Protein::~Protein(){}
    class Chicken : public Protein
    {
    public:
        Chicken():Protein(ChickenT){}
        ~Chicken(){}
    };
    class Pork : public Protein
    {
    public:
        Pork():Protein(PorkT){}
        ~Pork(){}
    };
    class Beef : public Protein
    {
    public:
        Beef():Protein(BeefT){}
        ~Beef(){}
    };
    Protein * Protein::NewProtein(ProteinType t)
    {
        switch (t)
        {
            case ChickenT: return new Chicken;
            case PorkT: return new Pork;
            case BeefT: return new Beef;
            default: return new Chicken;
        }
    }
    class Vege : public FoodBase
    {
        VegeType  m_vegeType;
    public:
        Vege(VegeType t = LettuceT):FoodBase(VegeT),m_vegeType(t){}
        VegeType GetVegeType() const {return m_vegeType;}
        virtual ~Vege() = 0;
        static Vege * NewVege(VegeType t);
    };
    Vege::~Vege(){}
    class Lettuce : public Vege
    {
    public:
        Lettuce():Vege(LettuceT){}
        ~Lettuce(){}
    };
    class Broccoli : public Vege
    {
    public:
        Broccoli():Vege(BroccoliT){}
        ~Broccoli(){}
    };
    Vege * Vege::NewVege(VegeType t)
    {
        switch (t)
        {
            case LettuceT: return new Lettuce;
            case BroccoliT: return new Broccoli;
            default: return new Lettuce;
        }
    }
    class Side : public FoodBase
    {
        SideType m_sideType;
    public:
        Side(SideType t = FriesT):FoodBase(SideT),m_sideType(t){}
        SideType GetSideType() const {return m_sideType;}
        virtual ~Side() = 0;
        static Side * NewSide(SideType t);
    };
    Side::~Side(){}
    class Fries : public Side
    {
    public:
        Fries():Side(FriesT){}
        ~Fries(){}
    };
    class Salad : public Side
    {
    public:
        Salad():Side(SaladT){}
        ~Salad(){}
    };
    class Soup : public Side
    {
    public:
        Soup():Side(SoupT){}
        ~Soup(){}
    };
    Side * Side::NewSide(SideType t)
    {
        switch(t)
        {
            case FriesT: return new Fries;
            case SaladT: return new Salad;
            case SoupT: return new Soup;
            default: return new Fries;
        }
    }

    class Meal
    {
        Protein * m_p;
        Vege * m_v;
        Side * m_s;
    public:
        Meal(Protein * p, Vege * v, Side * s):m_p(p),m_v(v),m_s(s){}
        std::string GetCompositeKey() const
        {
            return std::to_string(m_p->GetProteinType()) + std::to_string(m_v->GetVegeType()) + std::to_string(m_s->GetSideType());
        }
        ~Meal(){}
    };
    class Kitchen
    {
        const int m_proteinTypeCount = 3;
        const int m_vegeTypeCount = 2;
        const int m_sideTypeCount = 3;
        std::vector<int> m_proteinCount;
        std::vector<int> m_vegeCount;
        std::vector<int> m_sideCount;
        std::unordered_set<Meal*> m_meals;
        std::unordered_map<std::string,int> m_mealTypeCount;
    public:
        Kitchen(int chickenCount, int porkCount, int beefCount, int lettuceCount, int broccoliCount, int friesCount, int saladCount, int soupCount)
                :m_proteinCount({chickenCount,porkCount,beefCount}), m_vegeCount({lettuceCount,broccoliCount}), m_sideCount({friesCount,saladCount,soupCount})
        {
            int totalProteinCount = chickenCount+porkCount+beefCount;
            int totalVegeCount = lettuceCount+broccoliCount;
            int totalSideCount = friesCount+saladCount+soupCount;
            int proteinIdx = 0;
            int vegeIdx = 0;
            int sideIdx = 0;
            while (totalProteinCount != 0 && totalVegeCount != 0 && totalSideCount != 0)
            {
                //std::cout << proteinIdx << "," << vegeIdx << "," << sideIdx << std::endl;
                Meal * cur = new Meal(Protein::NewProtein((ProteinType)proteinIdx), Vege::NewVege((VegeType)vegeIdx), Side::NewSide((SideType)sideIdx));

                --totalProteinCount;
                --m_proteinCount[proteinIdx];
                --totalVegeCount;
                --m_vegeCount[vegeIdx];
                --totalSideCount;
                --m_sideCount[sideIdx];

                sideIdx = (sideIdx+1) % m_sideTypeCount;
                while (m_sideCount[sideIdx] == 0 && totalSideCount)
                    sideIdx = (sideIdx+1) % m_sideTypeCount;

                if (m_meals.size() % m_sideTypeCount == 0)
                {
                    vegeIdx = (vegeIdx+1) % m_vegeTypeCount;
                    while (m_vegeCount[vegeIdx] == 0 && totalVegeCount)
                        vegeIdx = (vegeIdx+1) % m_vegeTypeCount;
                }

                if (m_meals.size() % (m_vegeTypeCount * m_sideTypeCount) == 0)
                {
                    proteinIdx = (proteinIdx+1) % m_proteinTypeCount;
                    while (m_proteinCount[proteinIdx] == 0 && totalProteinCount)
                        proteinIdx = (proteinIdx+1) % m_proteinTypeCount;
                }

                m_meals.insert(cur);
                ++m_mealTypeCount[cur->GetCompositeKey()];
            }

            std::cout << Debug::ToStr1D<std::string,int>()(m_mealTypeCount) << std::endl;
            std::cout << "total meal = " << m_meals.size() << std::endl;
        }

    };
}
#endif
