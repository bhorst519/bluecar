#ifndef TASK_ID_HPP
#define TASK_ID_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "util.h"

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
namespace Vcu
{

enum class Task_E : uint8_t
{
    TASK_1KHZ,
    TASK_100HZ,
    TASK_10HZ,
    TASK_1HZ,
    TOTAL_TASKS
};

using TaskId = uint8_t;

struct Task1kHz     { constexpr operator TaskId() const { return static_cast<TaskId>(Task_E::TASK_1KHZ); } };
struct Task100Hz    { constexpr operator TaskId() const { return static_cast<TaskId>(Task_E::TASK_100HZ); } };
struct Task10Hz     { constexpr operator TaskId() const { return static_cast<TaskId>(Task_E::TASK_10HZ); } };
struct Task1Hz      { constexpr operator TaskId() const { return static_cast<TaskId>(Task_E::TASK_1HZ); } };

} // namespace Vcu

namespace Shared
{

using TaskId = Vcu::TaskId;

} // namespace Shared

#endif // TASK_ID_HPP
