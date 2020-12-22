#include <iostream>
#include "CLIWidget.hpp"

int main(int argc, char** argv) {
    CLIWidget::time_widget();
    NEWLINE
    PUT(CLIWidget::convert(BRANCH_SIGN) + "  ")
    
    CLIWidget::branch_widget();
    
    return 0;
}
