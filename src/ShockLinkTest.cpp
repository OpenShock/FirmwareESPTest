#include <Arduino.h>
#include "LRmtControl.h"
#include <vector>

rmt_obj_t *rmt_send = NULL;

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("==== ShockLink ESP TESTER v0.1.0");

    if ((rmt_send = rmtInit(15, RMT_TX_MODE, RMT_MEM_64)) == NULL)
    {
        Serial.println("init sender failed\n");
        return;
    }

    float realTick = rmtSetTick(rmt_send, 1000);
    Serial.printf("real tick set to: %fns\n", realTick);
}

void loop() {
  Serial.print("=>");
  std::vector<rmt_data_t> seq = LRmtControl::GetSequence(1337, 2, 99);
  rmtWriteBlocking(rmt_send, seq.data(), seq.size());
}