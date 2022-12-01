#include <string>

#include <NMXReadout.h>
#include <wrapper.h>


#ifdef __cplusplus
extern "C" {
#endif
  struct nmx_readout{
    void *obj;
  };

  // Create a new NMX Readout object
  nmx_readout_t * nmx_readout_create(char* address, int port){
    nmx_readout_t* br;
    NMXReadout *obj;

    std::string string_address(address);

    br = (nmx_readout_t*)malloc(sizeof(*br));
    obj = new NMXReadout(NMXReadout::Detector, string_address, port);
    br->obj = obj;

    return br;
  }

  // Destroy an existing BIFROST Readout object
  void nmx_readout_destroy(nmx_readout_t* br){
    if (br == NULL) return;
    delete static_cast<NMXReadout*>(br->obj);
    free(br);
  }

  // Add a readout value to the transmission buffer of the BIFROST Readout object
  // Automatically transmits the packet if it is full.
  void nmx_readout_add(
      nmx_readout_t* br, uint8_t Ring, uint8_t FEN, uint32_t TimeHigh, uint32_t TimeLow,
                 uint8_t VMM, uint8_t Channel
  )
  {
    NMXReadout* obj;
    if (br == NULL) return;
    obj = static_cast<NMXReadout*>(br->obj);
    obj->addReadout(Ring, FEN, TimeHigh, TimeLow,
                 VMM, Channel);
  }

  // Send the current data buffer for the BIFROST Readout object
  void nmx_readout_send(nmx_readout_t* br)
  {
    NMXReadout* obj;
    if (br == NULL) return;
    obj = static_cast<NMXReadout*>(br->obj);
    obj->send();
  }
  // Update the pulse and previous pulse times for the BIFROST Readout object
  void nmx_readout_setPulseTime(
      nmx_readout_t* br, uint32_t pulse_high, uint32_t pulse_low,
      uint32_t prev_high, uint32_t prev_low
  )
  {
    NMXReadout* obj;
    if (br == NULL) return;
    obj = static_cast<NMXReadout*>(br->obj);
    obj->setPulseTime(pulse_high, pulse_low, prev_high, prev_low);
  }
  // Initialize a new packet with no readouts for the BIFROST Readout object
  void nmx_readout_newPacket(nmx_readout_t* br)
  {
    NMXReadout* obj;
    if (br == NULL) return;
    obj = static_cast<NMXReadout*>(br->obj);
    obj->newPacket();
  }

  //
#ifdef __cplusplus
}
#endif
