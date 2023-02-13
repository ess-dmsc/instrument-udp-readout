#include <string>

#include <MiraclesReadout.h>
#include <wrapper.h>


#ifdef __cplusplus
extern "C" {
#endif
  struct miracles_readout{
    void *obj;
  };

  // Create a new MIRACLES Readout object
  miracles_readout_t * miracles_readout_create(char* address, int port){
    miracles_readout_t* br;
    MiraclesReadout *obj;

    std::string string_address(address);

    br = (miracles_readout_t*)malloc(sizeof(*br));
    obj = new MiraclesReadout(MiraclesReadout::Detector, string_address, port);
    br->obj = obj;

    return br;
  }

  // Destroy an existing MIRACLES Readout object
  void miracles_readout_destroy(miracles_readout_t* br){
    if (br == NULL) return;
    delete static_cast<MiraclesReadout*>(br->obj);
    free(br);
  }

  // Add a readout value to the transmission buffer of the MIRACLES Readout object
  // Automatically transmits the packet if it is full.
  void miracles_readout_add(
      miracles_readout_t* br, uint8_t ring, uint8_t fen,
      uint32_t time_high, uint32_t time_low,
      uint8_t tube, uint16_t amplitude_a, uint16_t amplitude_b
  )
  {
    MiraclesReadout* obj;
    if (br == NULL) return;
    obj = static_cast<MiraclesReadout*>(br->obj);
    obj->addReadout(ring, fen, time_high, time_low, tube, amplitude_a, amplitude_b);
  }

  // Send the current data buffer for the MIRACLES Readout object
  void miracles_readout_send(miracles_readout_t* br)
  {
    MiraclesReadout* obj;
    if (br == NULL) return;
    obj = static_cast<MiraclesReadout*>(br->obj);
    obj->send();
  }
  // Update the pulse and previous pulse times for the MIRACLES Readout object
  void miracles_readout_setPulseTime(
      miracles_readout_t* br, uint32_t pulse_high, uint32_t pulse_low,
      uint32_t prev_high, uint32_t prev_low
  )
  {
    MiraclesReadout* obj;
    if (br == NULL) return;
    obj = static_cast<MiraclesReadout*>(br->obj);
    obj->setPulseTime(pulse_high, pulse_low, prev_high, prev_low);
  }
  // Initialize a new packet with no readouts for the MIRACLES Readout object
  void miracles_readout_newPacket(miracles_readout_t* br)
  {
    MiraclesReadout* obj;
    if (br == NULL) return;
    obj = static_cast<MiraclesReadout*>(br->obj);
    obj->newPacket();
  }

  //
#ifdef __cplusplus
}
#endif
