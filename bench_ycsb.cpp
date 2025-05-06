#include "benchmark/ycsb/Database.h"
#include "core/Coordinator.h"
#include "core/Macros.h"

DEFINE_int32(read_write_ratio, 80, "read write ratio");
DEFINE_int32(read_only_ratio, 0, "read only transaction ratio");
DEFINE_int32(cross_ratio, 0, "cross partition transaction ratio");
DEFINE_int32(keys, 200000, "keys in a partition.");
DEFINE_double(zipf, 0, "skew factor");
DEFINE_string(skew_pattern, "both", "skew pattern: both, read, write");
DEFINE_bool(two_partitions, false, "dist transactions access two partitions.");
DEFINE_bool(pwv_ycsb_star, false, "ycsb keys dependency.");
DEFINE_bool(global_key_space, false, "ycsb global key space.");


// —— Add these two —— 
DEFINE_int32(barrier_delayed_percent,    0,    "percent of partitions to delay at the barrier");
DEFINE_int32(barrier_artificial_delay_ms,0,    "how many ms each delayed partition should sleep before entering barrier");


int main(int argc, char *argv[]) {

  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  google::ParseCommandLineFlags(&argc, &argv, true);

  aria::ycsb::Context context;
  SETUP_CONTEXT(context);

  if (FLAGS_skew_pattern == "both") {
    context.skewPattern = aria::ycsb::YCSBSkewPattern::BOTH;
  } else if (FLAGS_skew_pattern == "read") {
    context.skewPattern = aria::ycsb::YCSBSkewPattern::READ;
  } else if (FLAGS_skew_pattern == "write") {
    context.skewPattern = aria::ycsb::YCSBSkewPattern::WRITE;
  } else {
    CHECK(false);
  }

  context.readWriteRatio = FLAGS_read_write_ratio;
  context.readOnlyTransaction = FLAGS_read_only_ratio;
  context.crossPartitionProbability = FLAGS_cross_ratio;
  context.keysPerPartition = FLAGS_keys;
  context.two_partitions = FLAGS_two_partitions;
  context.pwv_ycsb_star = FLAGS_pwv_ycsb_star;
  context.global_key_space = FLAGS_global_key_space;

  // Pass the barrier delay flags into the context
  context.barrierDelayedPercent = FLAGS_barrier_delayed_percent;
  context.barrierArtificialDelayMs = FLAGS_barrier_artificial_delay_ms;

  if (FLAGS_zipf > 0) {
    context.isUniform = false;
    if (context.global_key_space) {
      aria::Zipf::globalZipf().init(
          context.keysPerPartition * context.partition_num, FLAGS_zipf);
    } else {
      aria::Zipf::globalZipf().init(context.keysPerPartition, FLAGS_zipf);
    }
  }

  aria::ycsb::Database db;
  db.initialize(context);

  // disable core‐pinning on this run
  context.cpu_affinity = false;

  aria::Coordinator c(FLAGS_id, db, context);
  c.connectToPeers();
  c.start();
  return 0;
}