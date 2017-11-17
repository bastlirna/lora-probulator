#include "menu.h"

#include "core.h"
#include "hal.h"
#include "lcd.h"
#include "lora.h"

// --- Menu Items -------------------------------------------------------------

struct DeviceSettingsMenuItem : MenuItem {
    
    const char * label() {
        return "Device";
    }

    String value() {
        return lora_dev_name(settings.currentDev);
    }

    void change() {
        settings.currentDev ++;

        if (settings.currentDev >= 3) {
            settings.currentDev = 0;
        }
    }

    void reset() {
        settings.currentDev = 0;
    }

    void apply() {
        lora_reset();
        runtime.periodicReset();
    }
};

struct PayloadSettingsMenuItem : MenuItem {

    const char * label() {
        return "Payload";
    }

    String value() {
        switch (settings.payloadType) {
            case PayloadEmpty:
                return "Empty";
            case PayloadTxt:
                return "TXT";
            case PayloadCounter:
                return "CTN";
            default:
                return "";
        }
    }

    void change() {
        int e = (int)settings.payloadType;
        
        settings.payloadType = (PayloadType)e;
    }

    void reset() {
        settings.payloadType = PayloadEmpty;
    }

    void apply() {
    }
};

struct ConfirmSettingsMenuItem : MenuItem {

    const char * label() {
        return "Confirmation";
    }

    String value() {
        return settings.confirm ? "YES" : "NO";
    }

    void change() {
        settings.confirm = !settings.confirm;
    }

    void reset() {
        settings.confirm = false;
    }

    void apply() {
        runtime.periodicReset();
    }
};

struct DownlinkSettingsMenuItem : MenuItem {
    
        const char * label() {
            return "Downlink";
        }
    
        String value() {
            return settings.donwlink ? "YES" : "NO";
        }
    
        void change() {
            settings.donwlink = !settings.donwlink;
        }

        void reset() {
            settings.donwlink = false;
        }
    
        void apply() {
            runtime.periodicReset();
        }
    };

struct PeriodicSettingsMenuItem : MenuItem {

    const char * label() {
        return "Periodic";
    }

    String value() {

        if (settings.interval == -1) {
            return "OFF";
        }

        return String(INTERVALS[settings.interval]);
    }

    void change() {
        settings.interval ++;
        if (settings.interval >= INTERVALS_LEN) settings.interval = -1;
    }

    void reset() {
        settings.interval = -1;
    }

    void apply() {
        if (settings.interval == -1) {
            runtime.periodic = false;
        } else {
            runtime.periodic = true;
        }
    }
};

struct SFSettingsMenuItem : MenuItem {

    const char * label() {
        return "Spreading factor";
    }

    String value() {
        return "SF" + String(settings.sf, 10);
    }

    void change() {
        settings.sf ++;
        if (settings.sf > 12) settings.sf = 7;
    }

    void reset() {
        settings.sf = 7;
    }

    void apply() {
        lora_change_sf(settings.sf);
    }
};

struct ScreenMirrorMenuItem : MenuItem {

    const char * label() {
        return "Screen mirror";
    }

    String value() {
        return settings.screenMirror ? "YES" : "NO";
    }

    void change() {
        settings.screenMirror = !settings.screenMirror;
    }

    void reset() {
        settings.screenMirror = false;
    }

    void apply() {
    }
};

struct AboutMenuItem : MenuItem {
    const char * label() {
        return "About";
    };

    String value() {
        return ">";
    };

    void change() {
        screenMgr.change(&about);
    }

    void reset() {
    }

    void apply() {
    }
};

struct ExitMenuItem : MenuItem {
    const char * label() {
        return "Exit";
    };

    String value() {
        return ">";
    };

    void change() {
        screenMgr.change(&home);
    }

    void reset() {
    }

    void apply() {
    }
};


// --- Menu Logic -------------------------------------------------------------

MenuScreen::MenuScreen() {

    byte i = 0;

    items[i++] = new DeviceSettingsMenuItem();
    items[i++] = new PeriodicSettingsMenuItem();
    items[i++] = new ConfirmSettingsMenuItem();
    items[i++] = new DownlinkSettingsMenuItem();
    items[i++] = new SFSettingsMenuItem();
    items[i++] = new PayloadSettingsMenuItem();
    
    items[i++] = new ScreenMirrorMenuItem();
    items[i++] = new AboutMenuItem();
    items[i++] = new ExitMenuItem();
    
    len = i;
}

void MenuScreen::enter() {
    current = 0;
    itemChanged = false;
    update();
}

void MenuScreen::leave() {
    if (itemChanged) {
        items[current]->apply();
    }

    
}

void MenuScreen::update() {
    lcd_menu();
    
    int start = 0;

    if (current >= 3) {
        start = current - 3;
    }

    for(int i = start; i < len && i < start + 4; i++) {
        
        lcd_menu_item(i-start, items[i]->label(), items[i]->value(), i == current);
    }

    lcd_update();
}

void MenuScreen::loop() {
}

// Next menu item
void MenuScreen::onAPress() {

    if (itemChanged) {
        items[current]->apply();
    }

    current ++;
    itemChanged = false;

    if (current >= len) {
        current = 0;
    }

    update();
}

void MenuScreen::onALongPress() {
    screenMgr.change(&home);
}

// CHange value
void MenuScreen::onBPress() {
    items[current]->change();
    itemChanged = true;
    update();
}

// CHange value
void MenuScreen::onBLongPress() {
    items[current]->reset();
    itemChanged = true;
    update();
}


/*MenuItem::MenuItem(const char *label) {
    this->label = label;
}*/
