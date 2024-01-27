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

class Sensors {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.encoder_eixo = null;
      this.encoder_as5600_R = null;
      this.encoder_as5600_L = null;
      this.angularVelocity = null;
    }
    else {
      if (initObj.hasOwnProperty('encoder_eixo')) {
        this.encoder_eixo = initObj.encoder_eixo
      }
      else {
        this.encoder_eixo = 0.0;
      }
      if (initObj.hasOwnProperty('encoder_as5600_R')) {
        this.encoder_as5600_R = initObj.encoder_as5600_R
      }
      else {
        this.encoder_as5600_R = 0.0;
      }
      if (initObj.hasOwnProperty('encoder_as5600_L')) {
        this.encoder_as5600_L = initObj.encoder_as5600_L
      }
      else {
        this.encoder_as5600_L = 0.0;
      }
      if (initObj.hasOwnProperty('angularVelocity')) {
        this.angularVelocity = initObj.angularVelocity
      }
      else {
        this.angularVelocity = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Sensors
    // Serialize message field [encoder_eixo]
    bufferOffset = _serializer.float64(obj.encoder_eixo, buffer, bufferOffset);
    // Serialize message field [encoder_as5600_R]
    bufferOffset = _serializer.float64(obj.encoder_as5600_R, buffer, bufferOffset);
    // Serialize message field [encoder_as5600_L]
    bufferOffset = _serializer.float64(obj.encoder_as5600_L, buffer, bufferOffset);
    // Serialize message field [angularVelocity]
    bufferOffset = _serializer.float64(obj.angularVelocity, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Sensors
    let len;
    let data = new Sensors(null);
    // Deserialize message field [encoder_eixo]
    data.encoder_eixo = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [encoder_as5600_R]
    data.encoder_as5600_R = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [encoder_as5600_L]
    data.encoder_as5600_L = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [angularVelocity]
    data.angularVelocity = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 32;
  }

  static datatype() {
    // Returns string type for a message object
    return 'my_project_msgs/Sensors';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '62f67af364bf00eab808407950937dc4';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 encoder_eixo
    float64 encoder_as5600_R
    float64 encoder_as5600_L
    float64 angularVelocity
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Sensors(null);
    if (msg.encoder_eixo !== undefined) {
      resolved.encoder_eixo = msg.encoder_eixo;
    }
    else {
      resolved.encoder_eixo = 0.0
    }

    if (msg.encoder_as5600_R !== undefined) {
      resolved.encoder_as5600_R = msg.encoder_as5600_R;
    }
    else {
      resolved.encoder_as5600_R = 0.0
    }

    if (msg.encoder_as5600_L !== undefined) {
      resolved.encoder_as5600_L = msg.encoder_as5600_L;
    }
    else {
      resolved.encoder_as5600_L = 0.0
    }

    if (msg.angularVelocity !== undefined) {
      resolved.angularVelocity = msg.angularVelocity;
    }
    else {
      resolved.angularVelocity = 0.0
    }

    return resolved;
    }
};

module.exports = Sensors;
