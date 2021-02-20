#pragma once
#include "Managers/Utils/SqlOperator/Logical/AndOperator.hpp"
#include "Managers/Utils/SqlOperator/Logical/OrOperator.hpp"
#include "Managers/Utils/SqlOperator/Logical/InOperator.hpp"
#include "Managers/Utils/SqlOperator/Logical/BetweenOperator.hpp"
#include "Managers/Utils/SqlOperator/Logical/NotOperator.hpp"
#include "Managers/Utils/SqlOperator/Comparison/GreaterOrEqualOperator.hpp"
#include "Managers/Utils/SqlOperator/Comparison/GreaterThanOperator.hpp"
#include "Managers/Utils/SqlOperator/Comparison/IsNotOperator.hpp"
#include "Managers/Utils/SqlOperator/Comparison/IsOperator.hpp"
#include "Managers/Utils/SqlOperator/Comparison/LessOrEqualOperator.hpp"
#include "Managers/Utils/SqlOperator/Comparison/LessThanOperator.hpp"
#include "Managers/Utils/SqlOperator/Comparison/LikeOperator.hpp"

using namespace BookManager::Manager::SqlOperator;

#define IS(field, value) std::make_shared<IsOperator<decltype(value)>>(field, value)
#define IS_NOT(field, value) std::make_shared<IsNotOperator<decltype(value)>>(field, value)
#define LT(field, value) std::make_shared<LessThanOperator<decltype(value)>>(field, value)
#define LTE(field, value) std::make_shared<LessOrEqualOperator<decltype(value)>>(field, value)
#define GT(field, value) std::make_shared<GreaterThanOperator<decltype(value)>>(field, value)
#define GTE(field, value) std::make_shared<GreaterOrEqualOperator<decltype(value)>>(field, value)
#define LIKE(field, value) std::make_shared<LikeOperator<decltype(value)>>(field, value)

#define AND(firstOperator, secondOperator) std::make_shared<AndOperator>(firstOperator, secondOperator)
#define OR(firstOperator, secondOperator) std::make_shared<OrOperator>(firstOperator, secondOperator)
#define NOT(firstOperator) std::make_shared<NotOperator>(firstOperator)
#define BETWEEN(field, firstValue, secondValue) std::make_shared<BetweenOperator<decltype(firstValue)>>(field, firstValue, secondValue)
#define IN(field, valueVector) std::make_shared<InOperator<decltype(valueVector)::value_type>>(field, valueVector)
