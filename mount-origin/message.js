/**
 * @fileoverview
 * @enhanceable
 * @suppress {messageConventions} JS Compiler reports an error if a variable or
 *     field starts with 'MSG_' and isn't a translatable message.
 * @public
 */
// GENERATED CODE -- DO NOT EDIT!

goog.provide('proto.Message');

goog.require('jspb.BinaryReader');
goog.require('jspb.BinaryWriter');
goog.require('jspb.Message');
goog.require('proto.MessageField');


/**
 * Generated by JsPbCodeGenerator.
 * @param {Array=} opt_data Optional initial data array, typically from a
 * server response, or constructed directly in Javascript. The array is used
 * in place and becomes part of the constructed object. It is not cloned.
 * If no data is provided, the constructed object will be empty, but still
 * valid.
 * @extends {jspb.Message}
 * @constructor
 */
proto.Message = function(opt_data) {
  jspb.Message.initialize(this, opt_data, 0, -1, proto.Message.repeatedFields_, null);
};
goog.inherits(proto.Message, jspb.Message);
if (goog.DEBUG && !COMPILED) {
  proto.Message.displayName = 'proto.Message';
}
/**
 * List of repeated fields within this message type.
 * @private {!Array<number>}
 * @const
 */
proto.Message.repeatedFields_ = [5];



if (jspb.Message.GENERATE_TO_OBJECT) {
/**
 * Creates an object representation of this proto suitable for use in Soy templates.
 * Field names that are reserved in JavaScript and will be renamed to pb_name.
 * To access a reserved field use, foo.pb_<name>, eg, foo.pb_default.
 * For the list of reserved names please see:
 *     com.google.apps.jspb.JsClassTemplate.JS_RESERVED_WORDS.
 * @param {boolean=} opt_includeInstance Whether to include the JSPB instance
 *     for transitional soy proto support: http://goto/soy-param-migration
 * @return {!Object}
 */
proto.Message.prototype.toObject = function(opt_includeInstance) {
  return proto.Message.toObject(opt_includeInstance, this);
};


/**
 * Static version of the {@see toObject} method.
 * @param {boolean|undefined} includeInstance Whether to include the JSPB
 *     instance for transitional soy proto support:
 *     http://goto/soy-param-migration
 * @param {!proto.Message} msg The msg instance to transform.
 * @return {!Object}
 * @suppress {unusedLocalVariables} f is only used for nested messages
 */
proto.Message.toObject = function(includeInstance, msg) {
  var f, obj = {
    proto: jspb.Message.getFieldWithDefault(msg, 1, ""),
    id: jspb.Message.getFieldWithDefault(msg, 2, 0),
    name: jspb.Message.getFieldWithDefault(msg, 3, ""),
    ts: jspb.Message.getFieldWithDefault(msg, 4, 0),
    fieldsList: jspb.Message.toObjectList(msg.getFieldsList(),
    proto.MessageField.toObject, includeInstance)
  };

  if (includeInstance) {
    obj.$jspbMessageInstance = msg;
  }
  return obj;
};
}


/**
 * Deserializes binary data (in protobuf wire format).
 * @param {jspb.ByteSource} bytes The bytes to deserialize.
 * @return {!proto.Message}
 */
proto.Message.deserializeBinary = function(bytes) {
  var reader = new jspb.BinaryReader(bytes);
  var msg = new proto.Message;
  return proto.Message.deserializeBinaryFromReader(msg, reader);
};


/**
 * Deserializes binary data (in protobuf wire format) from the
 * given reader into the given message object.
 * @param {!proto.Message} msg The message object to deserialize into.
 * @param {!jspb.BinaryReader} reader The BinaryReader to use.
 * @return {!proto.Message}
 */
proto.Message.deserializeBinaryFromReader = function(msg, reader) {
  while (reader.nextField()) {
    if (reader.isEndGroup()) {
      break;
    }
    var field = reader.getFieldNumber();
    switch (field) {
    case 1:
      var value = /** @type {string} */ (reader.readString());
      msg.setProto(value);
      break;
    case 2:
      var value = /** @type {number} */ (reader.readInt32());
      msg.setId(value);
      break;
    case 3:
      var value = /** @type {string} */ (reader.readString());
      msg.setName(value);
      break;
    case 4:
      var value = /** @type {number} */ (reader.readUint64());
      msg.setTs(value);
      break;
    case 5:
      var value = new proto.MessageField;
      reader.readMessage(value,proto.MessageField.deserializeBinaryFromReader);
      msg.addFields(value);
      break;
    default:
      reader.skipField();
      break;
    }
  }
  return msg;
};


/**
 * Serializes the message to binary data (in protobuf wire format).
 * @return {!Uint8Array}
 */
proto.Message.prototype.serializeBinary = function() {
  var writer = new jspb.BinaryWriter();
  proto.Message.serializeBinaryToWriter(this, writer);
  return writer.getResultBuffer();
};


/**
 * Serializes the given message to binary data (in protobuf wire
 * format), writing to the given BinaryWriter.
 * @param {!proto.Message} message
 * @param {!jspb.BinaryWriter} writer
 * @suppress {unusedLocalVariables} f is only used for nested messages
 */
proto.Message.serializeBinaryToWriter = function(message, writer) {
  var f = undefined;
  f = message.getProto();
  if (f.length > 0) {
    writer.writeString(
      1,
      f
    );
  }
  f = message.getId();
  if (f !== 0) {
    writer.writeInt32(
      2,
      f
    );
  }
  f = message.getName();
  if (f.length > 0) {
    writer.writeString(
      3,
      f
    );
  }
  f = message.getTs();
  if (f !== 0) {
    writer.writeUint64(
      4,
      f
    );
  }
  f = message.getFieldsList();
  if (f.length > 0) {
    writer.writeRepeatedMessage(
      5,
      f,
      proto.MessageField.serializeBinaryToWriter
    );
  }
};


/**
 * optional string proto = 1;
 * @return {string}
 */
proto.Message.prototype.getProto = function() {
  return /** @type {string} */ (jspb.Message.getFieldWithDefault(this, 1, ""));
};


/** @param {string} value */
proto.Message.prototype.setProto = function(value) {
  jspb.Message.setProto3StringField(this, 1, value);
};


/**
 * optional int32 id = 2;
 * @return {number}
 */
proto.Message.prototype.getId = function() {
  return /** @type {number} */ (jspb.Message.getFieldWithDefault(this, 2, 0));
};


/** @param {number} value */
proto.Message.prototype.setId = function(value) {
  jspb.Message.setProto3IntField(this, 2, value);
};


/**
 * optional string name = 3;
 * @return {string}
 */
proto.Message.prototype.getName = function() {
  return /** @type {string} */ (jspb.Message.getFieldWithDefault(this, 3, ""));
};


/** @param {string} value */
proto.Message.prototype.setName = function(value) {
  jspb.Message.setProto3StringField(this, 3, value);
};


/**
 * optional uint64 ts = 4;
 * @return {number}
 */
proto.Message.prototype.getTs = function() {
  return /** @type {number} */ (jspb.Message.getFieldWithDefault(this, 4, 0));
};


/** @param {number} value */
proto.Message.prototype.setTs = function(value) {
  jspb.Message.setProto3IntField(this, 4, value);
};


/**
 * repeated MessageField fields = 5;
 * @return {!Array<!proto.MessageField>}
 */
proto.Message.prototype.getFieldsList = function() {
  return /** @type{!Array<!proto.MessageField>} */ (
    jspb.Message.getRepeatedWrapperField(this, proto.MessageField, 5));
};


/** @param {!Array<!proto.MessageField>} value */
proto.Message.prototype.setFieldsList = function(value) {
  jspb.Message.setRepeatedWrapperField(this, 5, value);
};


/**
 * @param {!proto.MessageField=} opt_value
 * @param {number=} opt_index
 * @return {!proto.MessageField}
 */
proto.Message.prototype.addFields = function(opt_value, opt_index) {
  return jspb.Message.addToRepeatedWrapperField(this, 5, opt_value, proto.MessageField, opt_index);
};


proto.Message.prototype.clearFieldsList = function() {
  this.setFieldsList([]);
};


