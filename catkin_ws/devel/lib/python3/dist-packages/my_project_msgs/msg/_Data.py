# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from my_project_msgs/Data.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class Data(genpy.Message):
  _md5sum = "3376fc8753ba296918120944d2f95a14"
  _type = "my_project_msgs/Data"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """float64 Yaw_odom
float64 Yaw_mpu
float64 Yaw_combinado
float64 dist
float64 psi"""
  __slots__ = ['Yaw_odom','Yaw_mpu','Yaw_combinado','dist','psi']
  _slot_types = ['float64','float64','float64','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       Yaw_odom,Yaw_mpu,Yaw_combinado,dist,psi

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Data, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.Yaw_odom is None:
        self.Yaw_odom = 0.
      if self.Yaw_mpu is None:
        self.Yaw_mpu = 0.
      if self.Yaw_combinado is None:
        self.Yaw_combinado = 0.
      if self.dist is None:
        self.dist = 0.
      if self.psi is None:
        self.psi = 0.
    else:
      self.Yaw_odom = 0.
      self.Yaw_mpu = 0.
      self.Yaw_combinado = 0.
      self.dist = 0.
      self.psi = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_5d().pack(_x.Yaw_odom, _x.Yaw_mpu, _x.Yaw_combinado, _x.dist, _x.psi))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 40
      (_x.Yaw_odom, _x.Yaw_mpu, _x.Yaw_combinado, _x.dist, _x.psi,) = _get_struct_5d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_5d().pack(_x.Yaw_odom, _x.Yaw_mpu, _x.Yaw_combinado, _x.dist, _x.psi))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 40
      (_x.Yaw_odom, _x.Yaw_mpu, _x.Yaw_combinado, _x.dist, _x.psi,) = _get_struct_5d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_5d = None
def _get_struct_5d():
    global _struct_5d
    if _struct_5d is None:
        _struct_5d = struct.Struct("<5d")
    return _struct_5d