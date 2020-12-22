#include <iostream>
#include "CLIWidget.hpp"

int main(int argc, char** argv) {
    CLIWidget::time_widget();
    NEWLINE
    
    PUT(CLIWidget::convert(BRANCH_SIGN) + "  ")
    
    CLIWidget::branch_widget();
    
    CLIWidget::uptime_widget();
    NEWLINE

    return 0;
}
