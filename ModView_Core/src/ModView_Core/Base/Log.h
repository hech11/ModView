#pragma once
#include "mvpch.h"
#include <string.h>

// TODO : This needs to be properly implemented! ... For fun : )


#define MV_TRACE(x) std::cout << "[Trace]\t" << x;
#define MV_INFO(x) std::cout << "[Info]\t" << x;
#define MV_WARN(x) std::cout << "[Warn]\t" << x;
#define MV_ERROR(x) std::cout << "[ERROR]\t" << x;
#define MV_FATAL(x) std::cout << "[FATAL]\t" << x;