#ifndef  STOCKMARSHAL_H
#define  STOCKMARSHAL_H

#include  "MedusaClient.h"
#include  "TupleHeader.h"

////////////////////////////////////////////////////////////////////////////////
//
// Generated Martialing code for the Stock program.
//..............................................................................


using namespace Borealis;

class StockMarshal
{
  public:

    StockMarshal() {};
   ~StockMarshal() {};

    /// Activate the front-end and subscribe to streams.
    /// Returns 0 if okay; else an error occured.
    ///
    int32  open();


    /// Connect to inputs and subscribe to streams only.
    /// Similar to open() but does not load the query.
    ///
    void  openInputOutput();


    /// Run the client event loop.
    /// This does not return unless terminated or on an exception.
    ///
    void  runClient();


    /// Terminate the client event loop.
    ///
    void  terminateClient();


    /// Copy a string value to a fixed length array and zero fill.
    ///
    static void  setStringField(string  value,
                                  char  field[],
                                uint32  length)
                          throw(AuroraException);


    /// Get the timestamp for a tuple.
    ///
    static timeval   getTimeValue(uint8  *tuple)
    {
       return(*((timeval *)(tuple - HEADER_SIZE)));
    }


  public:

    struct PacketTuple
    {
        int32    time;
        double    price;
    } __attribute__((__packed__));

    struct  Packet : public TupleHeader
    {
        PacketTuple   _data;
    } __attribute__((__packed__));

    /// The sentPacket  method must be defined by the application.
    /// It is called after sendPacket is done and a pause.
    ///
    void  sentPacket();

    /// Enque a Packet for input.
    ///
    void  batchPacket(Packet  *tuple);

    /// Send enqued Packet inputs.
    ///
    void  sendPacket(uint32  sleep);

  private:

    /// Connect the Packet input stream.
    ///
    void  connectPacket();

    ///  Resume here.  Extend with a user callback.
    void  delayPacket();

  private:

    /// Handler to dispatch tuples received.
    ///
    static Status outputHandler(ptr<StreamEvent> event);


  public:

    struct AggregateTuple
    {
        int32    time;
        double    maxprice;
        int32    currenttime;
    } __attribute__((__packed__));

    /// The receivedAggregate method must be defined by the application.
    /// It is called after a(n) AggregateTuple is received.
    ///
    static void  receivedAggregate(AggregateTuple  *tuple);

  private:

    /// Subscribe to the Aggregate output stream.
    ///
    void  subscribeAggregate();

    /// Handler to receive tuples from the Aggregate stream.
    ///
    static Status  AggregateHandler(ptr<StreamEvent>  event);

  private:

    /// Launch the Borealis front-end.
    ///
    static int32  launchDiagram(string  xml);  // Path of an initial xml file.

    /// Client connections to Borealis nodes.
    ///
    MedusaClient      *_client;


    /// Event state for input streams.
    /// These are declared with a smart pointer as fast_post_event requires it.
    ///
    ptr<StreamEvent>   _eventPacket;
};

#endif                         // STOCKMARSHAL_H
