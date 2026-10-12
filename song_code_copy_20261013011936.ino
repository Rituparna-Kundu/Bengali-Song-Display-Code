// OLED Lyrics Display (SSD1306 128x64, I2C) - ESP32 / Arduino
// Libraries: Adafruit SSD1306 + Adafruit GFX
// ESP32 default I2C: SDA = GPIO21, SCL = GPIO22

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_W 128
#define SCREEN_H 64
#define OLED_ADDR 0x3C   // try 0x3D if blank

Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);

struct Line {
  unsigned long startMs;
  const char* text;
};

// ---- PUT YOUR LYRICS + TIMING HERE ----
Line lyrics[] = {
  {0,     "1" },
  {2000,  "2" },
  {4000,  "3" },
  {5000,  "Ekhon onek raat" },
  {7000,  "Tomar kadhe amar nisshash" },
  
  {9600,  "Ami beche achi" },
  {11000, "Tomar valobashai" },
  {15000, "Chuye dile haat" },
  {17000, "Amar briddho buke tomar matha" },
  {20000, "Chepe dhore tolchi" },
  {22000,  "Kemon neshai" }
};
const int TOTAL = sizeof(lyrics) / sizeof(lyrics[0]);

const int  TEXT_SIZE  = 2;
const bool TYPEWRITER = true;
const int  TYPE_DELAY = 40;   // ms per character
const bool LOOP       = true;

const int CHAR_W    = 6 * TEXT_SIZE;               // 12 px
const int ROW_H     = 8 * TEXT_SIZE;               // 16 px
const int MAX_CHARS = SCREEN_W / CHAR_W;           // 10 chars per row
const int MAX_ROWS  = SCREEN_H / ROW_H;            // 4 rows fit

String rowsBuf[8];
int rowCount = 0;

unsigned long t0;
int current = -1;

void pushRow(const String& r) {
  if (rowCount < 8) rowsBuf[rowCount++] = r;
}

// Word-wrap text into rowsBuf (max MAX_CHARS per row)
void wrapText(const char* txt) {
  rowCount = 0;
  String s = String(txt);
  String cur = "";
  int i = 0;

  while (i < (int)s.length()) {
    int sp = s.indexOf(' ', i);
    if (sp == -1) sp = s.length();
    String word = s.substring(i, sp);
    i = sp + 1;

    // very long word: split it
    while ((int)word.length() > MAX_CHARS) {
      if (cur.length()) { pushRow(cur); cur = ""; }
      pushRow(word.substring(0, MAX_CHARS));
      word = word.substring(MAX_CHARS);
    }

    if (cur.length() == 0) cur = word;
    else if ((int)(cur.length() + 1 + word.length()) <= MAX_CHARS) cur += " " + word;
    else { pushRow(cur); cur = word; }
  }
  if (cur.length()) pushRow(cur);
}

void drawWrapped(int visibleChars) {
  display.clearDisplay();
  display.setTextSize(TEXT_SIZE);
  display.setTextColor(SSD1306_WHITE);

  int rows = min(rowCount, MAX_ROWS);
  int y = (SCREEN_H - rows * ROW_H) / 2;

  int shown = 0;
  for (int r = 0; r < rows; r++) {
    String row = rowsBuf[r];
    int allow = visibleChars - shown;
    if (allow < 0) allow = 0;
    String part = row.substring(0, min((int)row.length(), allow));

    int w = row.length() * CHAR_W;               // center using full row width
    display.setCursor((SCREEN_W - w) / 2, y + r * ROW_H);
    display.print(part);

    shown += row.length();
  }
  display.display();
}

void showLine(const char* txt) {
  wrapText(txt);

  int total = 0;
  for (int r = 0; r < min(rowCount, MAX_ROWS); r++) total += rowsBuf[r].length();

  if (!TYPEWRITER) { drawWrapped(total); return; }
  for (int i = 0; i <= total; i++) {
    drawWrapped(i);
    delay(TYPE_DELAY);
  }
}

void setup() {
  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    for (;;);  // display not found
  }
  display.ssd1306_command(SSD1306_SETCONTRAST);
display.ssd1306_command(0xFF);   // max brightness
  display.clearDisplay();
  display.display();
  t0 = millis();
}

void loop() {
  unsigned long now = millis() - t0;

  for (int i = TOTAL - 1; i >= 0; i--) {
    if (now >= lyrics[i].startMs) {
      if (i != current) {
        current = i;
        showLine(lyrics[i].text);
      }
      break;
    }
  }

  if (LOOP && now > lyrics[TOTAL - 1].startMs + 3000) {
    t0 = millis();
    current = -1;
  }
}