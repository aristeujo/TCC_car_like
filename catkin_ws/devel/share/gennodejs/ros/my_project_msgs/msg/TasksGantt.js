// Auto-generated. Do not edit!

// (in-package my_project_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let TaskState = require('./TaskState.js');

//-----------------------------------------------------------

class TasksGantt {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.task_states = null;
      this.wcet_sensor_read = null;
      this.wcet_publish_ros = null;
      this.wcet_motor_control = null;
      this.wcet_send_gantt = null;
    }
    else {
      if (initObj.hasOwnProperty('task_states')) {
        this.task_states = initObj.task_states
      }
      else {
        this.task_states = [];
      }
      if (initObj.hasOwnProperty('wcet_sensor_read')) {
        this.wcet_sensor_read = initObj.wcet_sensor_read
      }
      else {
        this.wcet_sensor_read = 0.0;
      }
      if (initObj.hasOwnProperty('wcet_publish_ros')) {
        this.wcet_publish_ros = initObj.wcet_publish_ros
      }
      else {
        this.wcet_publish_ros = 0.0;
      }
      if (initObj.hasOwnProperty('wcet_motor_control')) {
        this.wcet_motor_control = initObj.wcet_motor_control
      }
      else {
        this.wcet_motor_control = 0.0;
      }
      if (initObj.hasOwnProperty('wcet_send_gantt')) {
        this.wcet_send_gantt = initObj.wcet_send_gantt
      }
      else {
        this.wcet_send_gantt = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type TasksGantt
    // Serialize message field [task_states]
    // Serialize the length for message field [task_states]
    bufferOffset = _serializer.uint32(obj.task_states.length, buffer, bufferOffset);
    obj.task_states.forEach((val) => {
      bufferOffset = TaskState.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [wcet_sensor_read]
    bufferOffset = _serializer.float32(obj.wcet_sensor_read, buffer, bufferOffset);
    // Serialize message field [wcet_publish_ros]
    bufferOffset = _serializer.float32(obj.wcet_publish_ros, buffer, bufferOffset);
    // Serialize message field [wcet_motor_control]
    bufferOffset = _serializer.float32(obj.wcet_motor_control, buffer, bufferOffset);
    // Serialize message field [wcet_send_gantt]
    bufferOffset = _serializer.float32(obj.wcet_send_gantt, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type TasksGantt
    let len;
    let data = new TasksGantt(null);
    // Deserialize message field [task_states]
    // Deserialize array length for message field [task_states]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.task_states = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.task_states[i] = TaskState.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [wcet_sensor_read]
    data.wcet_sensor_read = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [wcet_publish_ros]
    data.wcet_publish_ros = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [wcet_motor_control]
    data.wcet_motor_control = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [wcet_send_gantt]
    data.wcet_send_gantt = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 12 * object.task_states.length;
    return length + 20;
  }

  static datatype() {
    // Returns string type for a message object
    return 'my_project_msgs/TasksGantt';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5262c66c69965c8531fa37eba78e2a23';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    my_project_msgs/TaskState[] task_states
    float32 wcet_sensor_read
    float32 wcet_publish_ros
    float32 wcet_motor_control
    float32 wcet_send_gantt
    ================================================================================
    MSG: my_project_msgs/TaskState
    int32 task_index
    int32 state     
    uint32 timestamp
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new TasksGantt(null);
    if (msg.task_states !== undefined) {
      resolved.task_states = new Array(msg.task_states.length);
      for (let i = 0; i < resolved.task_states.length; ++i) {
        resolved.task_states[i] = TaskState.Resolve(msg.task_states[i]);
      }
    }
    else {
      resolved.task_states = []
    }

    if (msg.wcet_sensor_read !== undefined) {
      resolved.wcet_sensor_read = msg.wcet_sensor_read;
    }
    else {
      resolved.wcet_sensor_read = 0.0
    }

    if (msg.wcet_publish_ros !== undefined) {
      resolved.wcet_publish_ros = msg.wcet_publish_ros;
    }
    else {
      resolved.wcet_publish_ros = 0.0
    }

    if (msg.wcet_motor_control !== undefined) {
      resolved.wcet_motor_control = msg.wcet_motor_control;
    }
    else {
      resolved.wcet_motor_control = 0.0
    }

    if (msg.wcet_send_gantt !== undefined) {
      resolved.wcet_send_gantt = msg.wcet_send_gantt;
    }
    else {
      resolved.wcet_send_gantt = 0.0
    }

    return resolved;
    }
};

module.exports = TasksGantt;
