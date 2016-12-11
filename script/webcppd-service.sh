#!/bin/sh
# 
# File:   webcpp-service.sh
# Author: centos7
#
# Created on Oct 28, 2016, 5:14:35 AM
#
PID=""
PID_FILE=/var/run/webcppd.pid

function get_pid {
    if [ -e $PID_FILE ]; then
        PID=`cat $PID_FILE`
        echo $PID
    fi
}

function stop {
   get_pid
   if [ -z $PID ]; then
      echo "webcppd server is not running."
      exit 1
   else
      echo -n "Stopping webcppd server.."
      kill -9 $PID
      sleep 1
      echo ".. Done."
   fi
}


function start {
   get_pid
   if [ -z $PID ]; then
      echo  "Starting webcppd server.."
      /usr/local/bin/webcppd --config=/etc/webcppd/webcppd.properties --pidfile=$PID_FILE --daemon
      sleep 5
      get_pid
      echo "Done. PID=$PID"
   else
      echo "Webcppd server is already running, PID=$PID"
   fi
}

function restart {
   echo  "Restarting webcppd server.."
   get_pid
   if [ -z $PID ]; then
      start
   else
      stop
      sleep 10
      start
   fi
}


function status {
   get_pid
   if [ -z  $PID ]; then
      echo "Webcpp server is not running."
      exit 1
   else
      echo "Webcppd server is running, PID=$PID"
   fi
}

case "$1" in
   start)
      start
   ;;
   stop)
      stop
   ;;
   restart)
      restart
   ;;
   status)
      status
   ;;
   *)
      echo "Usage: $0 {start|stop|restart|status}"
esac
