#include "menu.h"

#include "core.h"
#include "hal.h"
#include "lcd.h"

// --- Menu Items -------------------------------------------------------------

struct PayloadSettingsMenuItem : MenuItem {
    
        bool state = false;
    
        const char * label() {
            return "Payload";
        }
    
        const char * value() {
            return state ? "[EMPTY]" : "[LIPSUM]";
        }
    
        void change() {
            state = !state;
        }
    };

struct ConfirmSettingsMenuItem : MenuItem {

    const char * label() {
        return "Confirm msg.";
    }

    const char * value() {
        return confirm ? "[Yes]" : "[No]";
    }

    void change() {
        confirm = !confirm;
    }
};

struct PeriodSettingsMenuItem : MenuItem {
    
        bool state = false;
    
        const char * label() {
            return "Periodic";
        }
    
        const char * value() {
            return state ? "[Yes]" : "[No]";
        }
    
        void change() {
            state = !state;
        }
    };

struct AboutMenuItem : MenuItem {
    const char * label() {
        return "About";
    };

    const char * value() {
        return ">";
    };

    void change() {
        screenMgr.change(&about);
    }
};

struct ExitMenuItem : MenuItem {
    const char * label() {
        return "Exit";
    };

    const char * value() {
        return ">";
    };

    void change() {
        screenMgr.change(&home);
    }
};


// --- Menu Logic -------------------------------------------------------------

MenuScreen::MenuScreen() {

    items[0] = new ConfirmSettingsMenuItem();
    //items[1] = new PeriodSettingsMenuItem();
    //items[2] = new PayloadSettingsMenuItem();
    
    items[1] = new AboutMenuItem();
    items[2] = new ExitMenuItem();
    

    /*items[2] = new MenuItem("Exit2");
    items[3] = new MenuItem("Exit3");
    items[4] = new MenuItem("Exit4");
    items[5] = new MenuItem("Exit5");
    */

    len = 3;

}

void MenuScreen::enter() {
    current = 0;
    update();
}

void MenuScreen::leave() {
    Serial.println("LEAVE Menu");
}

void MenuScreen::update() {
    lcd_menu();
    
    int start = 0;

    if (current >= 3) {
        start = current - 3;
    }

    Serial.print("---");
    Serial.print(start);
    Serial.println("---");

    for(int i = start; i < len && i < start + 4; i++) {

        Serial.print(i == current ? "> " : "  ");
        Serial.println(i);

        lcd_menu_item(i-start, items[i]->label(), items[i]->value(), i == current);
    }

    Serial.println("---");

    lcd_update();
}

void MenuScreen::loop() {
}

// Next menu item
void MenuScreen::onAPress() {
    current ++;

    if (current >= len) {
        current = 0;
    }

    update();
}

// CHange value
void MenuScreen::onBPress() {
    items[current]->change();
    update();
}

void MenuScreen::onALongPress() {
    screenMgr.change(&home);
}

/*MenuItem::MenuItem(const char *label) {
    this->label = label;
}*/
