//
// Created by Yair Shemer on 01/09/2019.
//
#include "GFNumber.h"
/**
 * This function will get 2 GFNumbers from the user and produce it's following calculations:
 * a+b
 * a-b
 * b-a
 * a*b
 * prime factors of a
 * prime factors of b
 * @return 0 upon success
 */
int main()
{
    GFNumber gfn1, gfn2;
    std::cin >> gfn1 >> gfn2;
    assert(!std::cin.fail());
    assert(gfn1.getField() == gfn2.getField());
    std::cout << gfn1 + gfn2 << std::endl;
    std::cout << gfn1 - gfn2 << std::endl;
    std::cout << gfn2 - gfn1 << std::endl;
    std::cout << gfn1 * gfn2 << std::endl;
    gfn1.printFactors();
    gfn2.printFactors();
    return EXIT_SUCCESS;
}