#ifndef _COUNT_NUM_OF_ATOMS_IN_CHEMICAL_FORMULA_H
#define _COUNT_NUM_OF_ATOMS_IN_CHEMICAL_FORMULA_H
#include "Debug.h"
/*
Leetcode: Number of Atoms
Given a chemical formula (given as a string), return the count of each atom.
An atomic element always starts with an uppercase character, then zero or more lowercase letters, representing the name.
1 or more digits representing the count of that element may follow if the count is greater than 1.
 If the count is 1, no digits will follow. For example, H2O and H2O2 are possible, but H1O2 is impossible.
Two formulas concatenated together produce another formula. For example, H2O2He3Mg4 is also a formula.
A formula placed in parentheses, and a count (optionally added) is also a formula. For example, (H2O2) and (H2O2)3 are formulas.
Given a formula, output the count of all elements as a string in the following form:
 the first name (in sorted order), followed by its count (if that count is more than 1), followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.
Example 1:
Input:
formula = "H2O"
Output: "H2O"
Explanation:
The count of elements are {'H': 2, 'O': 1}.
Example 2:
Input:
formula = "Mg(OH)2"
Output: "H2MgO2"
Explanation:
The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.
Example 3:
Input:
formula = "K4(ON(SO3)2)2"
Output: "K4N2O14S4"
Explanation:
The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.
 */
class CountNumOfAtomsInChemicalFormula
{
public:
    std::string Recur(std::string formula)
    {
        int i = 0;
        std::map<std::string, int> count = recur(formula, i);
        std::string res;
        for (auto & p : count)
            res += p.first + (p.second == 1 ? "" : std::to_string(p.second));

        std::cout << "CountNumOfAtomsInChemicalFormula Recur for " << formula << ": " << res << std::endl;
        return res;
    }
    std::map<std::string,int> recur(std::string & s, int & i)
    {
        int N = s.size();
        std::map<std::string, int> count;
        while (i < N)
        {
            if (s[i] == ')')
            {
                ++i;
                return count;
            }
            else if (s[i] == '(')
            {
                std::map<std::string,int> nxt = recur(s, ++i);
                int begin = i;
                while (i < N && isdigit(s[i]))
                    ++i;
                int num = begin==i ? 1 : stoi(s.substr(begin, i-begin));
                for (auto & p : nxt)
                    count[p.first] += p.second*num;
            }
            else //char
            {
                int begin = i;
                ++i;
                while (i < N && islower(s[i]))
                    ++i;
                int begin2 = i;
                while (i < N && isdigit(s[i]))
                    ++i;
                std::string atom = s.substr(begin, begin2-begin);
                int num = begin2==i ? 1 : stoi(s.substr(begin2, i-begin2));
                count[atom] += num;
            }
        }
        return count;
    }
};
/*
CountNumOfAtomsInChemicalFormula Recur for K4(ON(SO3)2)2: K4N2O14S4
 */
#endif
