// Auto-generated. Do not edit!

// (in-package my_project_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class TasksSchedule {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.task_sensor = null;
      this.task_motor_control = null;
      this.task_publish = null;
      this.task_scheduler = null;
    }
    else {
      if (initObj.hasOwnProperty('task_sensor')) {
        this.task_sensor = initObj.task_sensor
      }
      else {
        this.task_sensor = '';
      }
      if (initObj.hasOwnProperty('task_motor_control')) {
        this.task_motor_control = initObj.task_motor_control
      }
      else {
        this.task_motor_control = '';
      }
      if (initObj.hasOwnProperty('task_publish')) {
        this.task_publish = initObj.task_publish
      }
      else {
        this.task_publish = '';
      }
      if (initObj.hasOwnProperty('task_scheduler')) {
        this.task_scheduler = initObj.task_scheduler
      }
      else {
        this.task_scheduler = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type TasksSchedule
    // Serialize message field [task_sensor]
    bufferOffset = _serializer.string(obj.task_sensor, buffer, bufferOffset);
    // Serialize message field [task_motor_control]
    bufferOffset = _serializer.string(obj.task_motor_control, buffer, bufferOffset);
    // Serialize message field [task_publish]
    bufferOffset = _serializer.string(obj.task_publish, buffer, bufferOffset);
    // Serialize message field [task_scheduler]
    bufferOffset = _serializer.string(obj.task_scheduler, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type TasksSchedule
    let len;
    let data = new TasksSchedule(null);
    // Deserialize message field [task_sensor]
    data.task_sensor = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [task_motor_control]
    data.task_motor_control = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [task_publish]
    data.task_publish = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [task_scheduler]
    data.task_scheduler = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.task_sensor);
    length += _getByteLength(object.task_motor_control);
    length += _getByteLength(object.task_publish);
    length += _getByteLength(object.task_scheduler);
    return length + 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'my_project_msgs/TasksSchedule';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1f7390576d604b72feca1119d3cd344a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string task_sensor
    string task_motor_control
    string task_publish
    string task_scheduler
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new TasksSchedule(null);
    if (msg.task_sensor !== undefined) {
      resolved.task_sensor = msg.task_sensor;
    }
    else {
      resolved.task_sensor = ''
    }

    if (msg.task_motor_control !== undefined) {
      resolved.task_motor_control = msg.task_motor_control;
    }
    else {
      resolved.task_motor_control = ''
    }

    if (msg.task_publish !== undefined) {
      resolved.task_publish = msg.task_publish;
    }
    else {
      resolved.task_publish = ''
    }

    if (msg.task_scheduler !== undefined) {
      resolved.task_scheduler = msg.task_scheduler;
    }
    else {
      resolved.task_scheduler = ''
    }

    return resolved;
    }
};

module.exports = TasksSchedule;
