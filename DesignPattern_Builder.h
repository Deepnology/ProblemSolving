#ifndef _DESIGN_PATTERN_BUILDER_H
#define _DESIGN_PATTERN_BUILDER_H
#include "Debug.h"
namespace DesignPattern_Builder
{
    enum EntreeEnum
    {
        chicken = 0,
        pork = 1,
        beef = 2,
        seaFood = 3,
    };
    enum SideEnum
    {
        fries = 0,
        salad = 1,
        soup = 2,
    };
    enum DrinkEnum
    {
        coke = 0,
        juice = 1,
    };
    class Meal
    {
        EntreeEnum m_entree;
        SideEnum m_side;
        DrinkEnum m_drink;
    public:
        Meal(){}
        ~Meal(){}
        void SetEntree(EntreeEnum e) { m_entree = e; }
        void SetSide(SideEnum s) { m_side = s; }
        void SetDrink(DrinkEnum d) { m_drink = d; }
    };
    class ComboMealBuilder
    {
    protected:
        Meal * m_meal;
    public:
        ComboMealBuilder():m_meal(new Meal){}
        virtual ~ComboMealBuilder() = 0;
        virtual void SetEntree(){}
        virtual void SetSide(){}
        virtual void SetDrink(){}
        Meal * GetMeal(){ return m_meal; }
    };
    ComboMealBuilder::~ComboMealBuilder() {}

    class ChickenComboBuilder : public ComboMealBuilder
    {
    public:
        ChickenComboBuilder() : ComboMealBuilder(){}
        ~ChickenComboBuilder(){}
        void SetEntree()
        {
            m_meal->SetEntree(chicken);
        }
        void SetSide()
        {
            m_meal->SetSide(fries);
        }
        void SetDrink()
        {
            m_meal->SetDrink(coke);
        }
    };

    class SeaFoodComboBuilder : public ComboMealBuilder
    {
    public:
        SeaFoodComboBuilder() : ComboMealBuilder(){}
        ~SeaFoodComboBuilder(){}
        void SetEntree()
        {
            m_meal->SetEntree(seaFood);
        }
        void SetSide()
        {
            m_meal->SetSide(salad);
        }
        void SetDrink()
        {
            m_meal->SetDrink(juice);
        }
    };

    class Kitchen
    {
        ComboMealBuilder * m_builder;
    public:
        Kitchen(ComboMealBuilder * builder):m_builder(builder){}
        ~Kitchen(){}
        Meal * GetMeal() { return m_builder->GetMeal(); }
        void BuildMeal()
        {
            m_builder->SetEntree();
            m_builder->SetSide();
            m_builder->SetDrink();
        }
    };

    
    void Test()
    {
        ComboMealBuilder * chickenComboBuilder = new ChickenComboBuilder;
        Kitchen * kitchen = new Kitchen(chickenComboBuilder);
        kitchen->BuildMeal();
        Meal * chickenCombo = kitchen->GetMeal();

        delete chickenCombo;
        delete kitchen;
        delete chickenComboBuilder;
    }
}
#endif
