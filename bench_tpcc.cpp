#include "benchmark/tpcc/Database.h"
#include "core/Coordinator.h"
#include "core/Macros.h"

DEFINE_bool(operation_replication, false, "use operation replication");
DEFINE_string(query, "neworder", "tpcc query, mixed, neworder, payment");
DEFINE_int32(neworder_dist, 10, "new order distributed.");
DEFINE_int32(payment_dist, 15, "payment distributed.");
DEFINE_int32(n_district, 10, "no. of districts in a warehouse");
DEFINE_bool(write_to_w_ytd, true, "by default, we run standard tpc-c.");
DEFINE_bool(payment_look_up, false, "look up C_ID on secondary index.");

DEFINE_int32(barrier_delayed_percent,    0,    "percent (out of 1000) of partitions to delay at the barrier");
DEFINE_int32(barrier_artificial_delay_ms,0,    "how many ms each delayed partition should sleep before entering barrier");

int main(int argc, char *argv[]) {

  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  google::ParseCommandLineFlags(&argc, &argv, true);

  aria::tpcc::Context context;
  SETUP_CONTEXT(context);

  context.operation_replication = FLAGS_operation_replication;

  if (FLAGS_query == "mixed") {
    context.workloadType = aria::tpcc::TPCCWorkloadType::MIXED;
  } else if (FLAGS_query == "neworder") {
    context.workloadType = aria::tpcc::TPCCWorkloadType::NEW_ORDER_ONLY;
  } else if (FLAGS_query == "payment") {
    context.workloadType = aria::tpcc::TPCCWorkloadType::PAYMENT_ONLY;
  } else {
    CHECK(false);
  }

  context.newOrderCrossPartitionProbability = FLAGS_neworder_dist;
  context.paymentCrossPartitionProbability = FLAGS_payment_dist;
  context.n_district = FLAGS_n_district;
  context.write_to_w_ytd = FLAGS_write_to_w_ytd;
  context.payment_look_up = FLAGS_payment_look_up;

  // Pass the barrier delay flags into the context
  context.barrierDelayedPercent = FLAGS_barrier_delayed_percent;
  context.barrierArtificialDelayMs = FLAGS_barrier_artificial_delay_ms;

  aria::tpcc::Database db;
  db.initialize(context);

  aria::Coordinator c(FLAGS_id, db, context);
  c.connectToPeers();
  c.start();
  return 0;
}