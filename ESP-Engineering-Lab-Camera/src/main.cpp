#include <Arduino.h>
#include <esp_camera.h>

#define PWDN_GPIO_NUM    -1
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM    15
#define SIOD_GPIO_NUM     4
#define SIOC_GPIO_NUM     5

#define Y9_GPIO_NUM      16
#define Y8_GPIO_NUM      17
#define Y7_GPIO_NUM      18
#define Y6_GPIO_NUM      12
#define Y5_GPIO_NUM      11
#define Y4_GPIO_NUM      10
#define Y3_GPIO_NUM       9
#define Y2_GPIO_NUM       8
#define VSYNC_GPIO_NUM    6
#define HREF_GPIO_NUM     7
#define PCLK_GPIO_NUM    13



bool initCamera() {
    Serial.println("Starting camera initialization...");
    Serial.println("Calling esp_camera_init()");

    camera_config_t config = {};

    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;

    config.pin_d0 = 11;
    config.pin_d1 = 9;
    config.pin_d2 = 8;
    config.pin_d3 = 10;
    config.pin_d4 = 12;
    config.pin_d5 = 18;
    config.pin_d6 = 17;
    config.pin_d7 = 16;

    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;

    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;

    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;

    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    config.frame_size = FRAMESIZE_QQVGA;
    config.jpeg_quality = 20;
    config.fb_count = 2;

    config.fb_location = CAMERA_FB_IN_PSRAM;

    Serial.println("Starting camera initialization...");

    esp_err_t err = esp_camera_init(&config);

    if (err != ESP_OK) {
        Serial.printf("CAMERA INIT FAILED: 0x%x\n", err);
        return false;
    }

    Serial.println("CAMERA INIT SUCCESS!");

    return true;
}

void setup() {
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("================================");
  Serial.println("ESP32-S3 CAMERA NODE");
  Serial.println("================================");

  Serial.print("PSRAM size: ");
  Serial.print(ESP.getPsramSize() / (1024 * 1024));
  Serial.println(" MB");

  Serial.print("Free PSRAM: ");
  Serial.print(ESP.getFreePsram() / (1024 * 1024));
  Serial.println(" MB");

  Serial.println("================================");

  if(initCamera()) {
    Serial.println("Camera initialized successfully.");

    Serial.println("GETTING SENSOR POINTER...");

    sensor_t *sensor = esp_camera_sensor_get();

    if (sensor == nullptr) {
      Serial.println("❌ SENSOR POINTER IS NULL");
    } else {
      Serial.println("✅ SENSOR POINTER IS VALID");
      Serial.printf("Sensor PID: 0x%02X\n", sensor->id.PID);
    }

    Serial.println("SENSOR TEST FINISHED");
    Serial.println("TESTING CAMERA FRAME CAPTURE...");

    camera_fb_t *fb = esp_camera_fb_get();

    if (!fb) {
      Serial.println("❌ FRAME CAPTURE FAILED");
      Serial.println("Possible sensor/pin/config issue");
    } 
    else {
      Serial.printf("IMAGE_SIZE:%u\n", fb->len);
      // a marker so the PC knows a img is starting
      Serial.println("IMAGE_START");

      //raw JPEG bytes
      Serial.write(fb->buf, fb->len);
      Serial.flush();
      //img finished
      Serial.println("\nIMAGE_END");

      esp_camera_fb_return(fb);

      Serial.println("✅ IMAGE SENT !!");
    }

    Serial.println("================================");
  }

  else {
    Serial.println("Camera initialization failed.");
  }
}


void loop() {
  delay(2000);

  Serial.print("S3 CAMERA NODE ALIVE ");
}

/*

We're going to use the crash location to 
narrow this down instead of throwing another 
500 lines of ESP32 code at it.

Problem: null-pointer-style crash during camera setup.

*/