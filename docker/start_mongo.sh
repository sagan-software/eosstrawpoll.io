#!/bin/bash
echo "Waiting for startup.."
until mongo --host mongo-master:27017 --eval 'quit(db.runCommand({ ping: 1 }).ok ? 0 : 2)' &>/dev/null; do
  printf '.'
  sleep 1
done

echo "Started.."

echo SETUP.sh time now: `date +"%T" `
mongo --host mongo-master:27017 <<EOF
   var cfg = {
        "_id": "rs",
        "version": 1,
        "members": [
            {
                "_id": 0,
                "host": "mongo-master:27017",
                "priority": 2
            },
            {
                "_id": 1,
                "host": "mongo-slave1:27017",
                "priority": 0
            },
            {
                "_id": 2,
                "host": "mongo-slave2:27017",
                "priority": 0
            }
        ]
    };
    rs.initiate(cfg, { force: true });
    rs.reconfig(cfg, { force: true });
    db.getMongo().setReadPref('nearest');
EOF

tail -f /dev/null
