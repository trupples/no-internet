#include "Color.h"

const std::string color_esc_fg(Color color)
{
    const std::string fg[] {
        "\033[30m", "\033[31m", "\033[32m", "\033[33m",
        "\033[34m", "\033[35m", "\033[36m", "\033[37m",
        "\033[90m", "\033[91m", "\033[92m", "\033[93m",
        "\033[94m", "\033[95m", "\033[96m", "\033[97m", ""
    };
    return fg[(unsigned char)color];
}

const std::string color_esc_bg(Color color)
{
    const std::string bg[] {
        "\033[40m", "\033[41m", "\033[42m", "\033[43m",
        "\033[44m", "\033[45m", "\033[46m", "\033[47m",
        "\033[100m", "\033[101m", "\033[102m", "\033[103m",
        "\033[104m", "\033[105m", "\033[106m", "\033[107m", ""
    };
    return bg[(unsigned char)color];
}
