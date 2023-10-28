from osrf/ros:noetic-desktop-focal
RUN /bin/bash -c "source /opt/ros/$ROS_DISTRO/setup.bash && mkdir -p /root/catkin_ws/src && cd /root/catkin_ws/ && catkin_make"
RUN echo "source /opt/ros/$ROS_DISTRO/setup.bash \nsource /root/catkin_ws/devel/setup.bash\n" >>/root/.bashrc
RUN apt-get update && apt-get -y install gedit
WORKDIR /root/catkin_ws/