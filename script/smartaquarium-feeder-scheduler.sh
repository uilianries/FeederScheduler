#!/bin/sh
### BEGIN INIT INFO
# Provides:          feeder-scheduler
# Required-Start:    $local_fs $network
# Required-Stop:     $local_fs $network
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# X-Interactive:     false
# Short-Description: SmartAquarium Feeder Scheduler
# Description:       SmartAquarium Feeder Scheduler
### END INIT INFO
NAME=feeder_scheduler
DESC="SmartAquarium Feeder Scheduler"
PIDFILE="/var/run/${NAME}.pid"
LOGFILE="/var/log/${NAME}.log"

# PHP binary path
DAEMON="/usr/local/bin/$NAME"

# Path of your php script
DAEMON_OPTS=""

START_OPTS="--start --background --make-pidfile --pidfile ${PIDFILE} --exec ${DAEMON} ${DAEMON_OPTS}"
STOP_OPTS="--stop --pidfile ${PIDFILE}"

test -x ${DAEMON} || exit 0

set -e

case "$1" in
    start)
        echo -n "Starting ${DESC}: "
        start-stop-daemon ${START_OPTS} >> ${LOGFILE}
        echo "$NAME."
        ;;
    stop)
        echo -n "Stopping $DESC: "
        start-stop-daemon ${STOP_OPTS}
        echo "$NAME."
        rm -f ${PIDFILE}
        ;;
    restart|force-reload)
        echo -n "Restarting $DESC: "
        start-stop-daemon ${STOP_OPTS}
        sleep 1
        start-stop-daemon ${START_OPTS} >> ${LOGFILE}
        echo "$NAME."
        ;;
    *)
        N=/etc/init.d/${NAME}
        echo "Usage: $N {start|stop|restart|force-reload}" >&2
        exit 1
        ;;
esac

exit 0