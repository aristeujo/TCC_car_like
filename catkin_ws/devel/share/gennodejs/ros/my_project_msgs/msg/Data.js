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

class Data {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Yaw_odom = null;
      this.Yaw_mpu = null;
      this.Yaw_combinado = null;
      this.dist = null;
      this.psi = null;
    }
    else {
      if (initObj.hasOwnProperty('Yaw_odom')) {
        this.Yaw_odom = initObj.Yaw_odom
      }
      else {
        this.Yaw_odom = 0.0;
      }
      if (initObj.hasOwnProperty('Yaw_mpu')) {
        this.Yaw_mpu = initObj.Yaw_mpu
      }
      else {
        this.Yaw_mpu = 0.0;
      }
      if (initObj.hasOwnProperty('Yaw_combinado')) {
        this.Yaw_combinado = initObj.Yaw_combinado
      }
      else {
        this.Yaw_combinado = 0.0;
      }
      if (initObj.hasOwnProperty('dist')) {
        this.dist = initObj.dist
      }
      else {
        this.dist = 0.0;
      }
      if (initObj.hasOwnProperty('psi')) {
        this.psi = initObj.psi
      }
      else {
        this.psi = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Data
    // Serialize message field [Yaw_odom]
    bufferOffset = _serializer.float64(obj.Yaw_odom, buffer, bufferOffset);
    // Serialize message field [Yaw_mpu]
    bufferOffset = _serializer.float64(obj.Yaw_mpu, buffer, bufferOffset);
    // Serialize message field [Yaw_combinado]
    bufferOffset = _serializer.float64(obj.Yaw_combinado, buffer, bufferOffset);
    // Serialize message field [dist]
    bufferOffset = _serializer.float64(obj.dist, buffer, bufferOffset);
    // Serialize message field [psi]
    bufferOffset = _serializer.float64(obj.psi, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Data
    let len;
    let data = new Data(null);
    // Deserialize message field [Yaw_odom]
    data.Yaw_odom = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [Yaw_mpu]
    data.Yaw_mpu = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [Yaw_combinado]
    data.Yaw_combinado = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dist]
    data.dist = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [psi]
    data.psi = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 40;
  }

  static datatype() {
    // Returns string type for a message object
    return 'my_project_msgs/Data';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3376fc8753ba296918120944d2f95a14';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 Yaw_odom
    float64 Yaw_mpu
    float64 Yaw_combinado
    float64 dist
    float64 psi
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Data(null);
    if (msg.Yaw_odom !== undefined) {
      resolved.Yaw_odom = msg.Yaw_odom;
    }
    else {
      resolved.Yaw_odom = 0.0
    }

    if (msg.Yaw_mpu !== undefined) {
      resolved.Yaw_mpu = msg.Yaw_mpu;
    }
    else {
      resolved.Yaw_mpu = 0.0
    }

    if (msg.Yaw_combinado !== undefined) {
      resolved.Yaw_combinado = msg.Yaw_combinado;
    }
    else {
      resolved.Yaw_combinado = 0.0
    }

    if (msg.dist !== undefined) {
      resolved.dist = msg.dist;
    }
    else {
      resolved.dist = 0.0
    }

    if (msg.psi !== undefined) {
      resolved.psi = msg.psi;
    }
    else {
      resolved.psi = 0.0
    }

    return resolved;
    }
};

module.exports = Data;
