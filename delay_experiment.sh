./bench_ycsb --logtostderr=1 --id=0 --servers="127.0.0.1:10004" --protocol=Aria --partition_num=1 --threads=1 --batch_size=1000 --read_write_ratio=80 --cross_ratio=100 --keys=40000 --zipf=0.0 --barrier_delayed_percent=1000 --barrier_artificial_delay_ms=3000

./bench_ycsb --logtostderr=1 --id=0 --servers="127.0.0.1:10004" --protocol=Aria --partition_num=1 --threads=1 --batch_size=1000 --read_write_ratio=80 --cross_ratio=100 --keys=40000 --zipf=0.0 --barrier_delayed_percent=100 --barrier_artificial_delay_ms=3000

./bench_ycsb --logtostderr=1 --id=0 --servers="127.0.0.1:10004" --protocol=Aria --partition_num=1 --threads=1 --batch_size=1000 --read_write_ratio=80 --cross_ratio=100 --keys=40000 --zipf=0.0 --barrier_delayed_percent=20 --barrier_artificial_delay_ms=3000

./bench_ycsb --logtostderr=1 --id=0 --servers="127.0.0.1:10004" --protocol=Aria --partition_num=1 --threads=1 --batch_size=1000 --read_write_ratio=80 --cross_ratio=100 --keys=40000 --zipf=0.0 --barrier_delayed_percent=5 --barrier_artificial_delay_ms=3000

./bench_ycsb --logtostderr=1 --id=0 --servers="127.0.0.1:10004" --protocol=Aria --partition_num=1 --threads=1 --batch_size=1000 --read_write_ratio=80 --cross_ratio=100 --keys=40000 --zipf=0.0 --barrier_delayed_percent=1 --barrier_artificial_delay_ms=3000