/**
 * @fileoverview
 * @enhanceable
 * @suppress {messageConventions} JS Compiler reports an error if a variable or
 *     field starts with 'MSG_' and isn't a translatable message.
 * @public
 */
// GENERATED CODE -- DO NOT EDIT!

goog.provide('proto.ComMessage');

goog.require('jspb.BinaryReader');
goog.require('jspb.BinaryWriter');
goog.require('jspb.Message');
goog.require('proto.Message');

goog.forwardDeclare('proto.ComMessageType');

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
proto.ComMessage = function(opt_data) {
  jspb.Message.initialize(this, opt_data, 0, -1, proto.ComMessage.repeatedFields_, null);
};
goog.inherits(proto.ComMessage, jspb.Message);
if (goog.DEBUG && !COMPILED) {
  proto.ComMessage.displayName = 'proto.ComMessage';
}
/**
 * List of repeated fields within this message type.
 * @private {!Array<number>}
 * @const
 */
proto.ComMessage.repeatedFields_ = [2,3,4];



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
proto.ComMessage.prototype.toObject = function(opt_includeInstance) {
  return proto.ComMessage.toObject(opt_includeInstance, this);
};


/**
 * Static version of the {@see toObject} method.
 * @param {boolean|undefined} includeInstance Whether to include the JSPB
 *     instance for transitional soy proto support:
 *     http://goto/soy-param-migration
 * @param {!proto.ComMessage} msg The msg instance to transform.
 * @return {!Object}
 * @suppress {unusedLocalVariables} f is only used for nested messages
 */
proto.ComMessage.toObject = function(includeInstance, msg) {
  var f, obj = {
    type: jspb.Message.getFieldWithDefault(msg, 1, 0),
    availMessagesList: jspb.Message.toObjectList(msg.getAvailMessagesList(),
    proto.Message.toObject, includeInstance),
    payloadList: jspb.Message.toObjectList(msg.getPayloadList(),
    proto.Message.toObject, includeInstance),
    reqMessagesList: jspb.Message.toObjectList(msg.getReqMessagesList(),
    proto.Message.toObject, includeInstance)
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
 * @return {!proto.ComMessage}
 */
proto.ComMessage.deserializeBinary = function(bytes) {
  var reader = new jspb.BinaryReader(bytes);
  var msg = new proto.ComMessage;
  return proto.ComMessage.deserializeBinaryFromReader(msg, reader);
};


/**
 * Deserializes binary data (in protobuf wire format) from the
 * given reader into the given message object.
 * @param {!proto.ComMessage} msg The message object to deserialize into.
 * @param {!jspb.BinaryReader} reader The BinaryReader to use.
 * @return {!proto.ComMessage}
 */
proto.ComMessage.deserializeBinaryFromReader = function(msg, reader) {
  while (reader.nextField()) {
    if (reader.isEndGroup()) {
      break;
    }
    var field = reader.getFieldNumber();
    switch (field) {
    case 1:
      var value = /** @type {!proto.ComMessageType} */ (reader.readEnum());
      msg.setType(value);
      break;
    case 2:
      var value = new proto.Message;
      reader.readMessage(value,proto.Message.deserializeBinaryFromReader);
      msg.addAvailMessages(value);
      break;
    case 3:
      var value = new proto.Message;
      reader.readMessage(value,proto.Message.deserializeBinaryFromReader);
      msg.addPayload(value);
      break;
    case 4:
      var value = new proto.Message;
      reader.readMessage(value,proto.Message.deserializeBinaryFromReader);
      msg.addReqMessages(value);
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
proto.ComMessage.prototype.serializeBinary = function() {
  var writer = new jspb.BinaryWriter();
  proto.ComMessage.serializeBinaryToWriter(this, writer);
  return writer.getResultBuffer();
};


/**
 * Serializes the given message to binary data (in protobuf wire
 * format), writing to the given BinaryWriter.
 * @param {!proto.ComMessage} message
 * @param {!jspb.BinaryWriter} writer
 * @suppress {unusedLocalVariables} f is only used for nested messages
 */
proto.ComMessage.serializeBinaryToWriter = function(message, writer) {
  var f = undefined;
  f = message.getType();
  if (f !== 0.0) {
    writer.writeEnum(
      1,
      f
    );
  }
  f = message.getAvailMessagesList();
  if (f.length > 0) {
    writer.writeRepeatedMessage(
      2,
      f,
      proto.Message.serializeBinaryToWriter
    );
  }
  f = message.getPayloadList();
  if (f.length > 0) {
    writer.writeRepeatedMessage(
      3,
      f,
      proto.Message.serializeBinaryToWriter
    );
  }
  f = message.getReqMessagesList();
  if (f.length > 0) {
    writer.writeRepeatedMessage(
      4,
      f,
      proto.Message.serializeBinaryToWriter
    );
  }
};


/**
 * optional ComMessageType type = 1;
 * @return {!proto.ComMessageType}
 */
proto.ComMessage.prototype.getType = function() {
  return /** @type {!proto.ComMessageType} */ (jspb.Message.getFieldWithDefault(this, 1, 0));
};


/** @param {!proto.ComMessageType} value */
proto.ComMessage.prototype.setType = function(value) {
  jspb.Message.setProto3EnumField(this, 1, value);
};


/**
 * repeated Message avail_messages = 2;
 * @return {!Array<!proto.Message>}
 */
proto.ComMessage.prototype.getAvailMessagesList = function() {
  return /** @type{!Array<!proto.Message>} */ (
    jspb.Message.getRepeatedWrapperField(this, proto.Message, 2));
};


/** @param {!Array<!proto.Message>} value */
proto.ComMessage.prototype.setAvailMessagesList = function(value) {
  jspb.Message.setRepeatedWrapperField(this, 2, value);
};


/**
 * @param {!proto.Message=} opt_value
 * @param {number=} opt_index
 * @return {!proto.Message}
 */
proto.ComMessage.prototype.addAvailMessages = function(opt_value, opt_index) {
  return jspb.Message.addToRepeatedWrapperField(this, 2, opt_value, proto.Message, opt_index);
};


proto.ComMessage.prototype.clearAvailMessagesList = function() {
  this.setAvailMessagesList([]);
};


/**
 * repeated Message payload = 3;
 * @return {!Array<!proto.Message>}
 */
proto.ComMessage.prototype.getPayloadList = function() {
  return /** @type{!Array<!proto.Message>} */ (
    jspb.Message.getRepeatedWrapperField(this, proto.Message, 3));
};


/** @param {!Array<!proto.Message>} value */
proto.ComMessage.prototype.setPayloadList = function(value) {
  jspb.Message.setRepeatedWrapperField(this, 3, value);
};


/**
 * @param {!proto.Message=} opt_value
 * @param {number=} opt_index
 * @return {!proto.Message}
 */
proto.ComMessage.prototype.addPayload = function(opt_value, opt_index) {
  return jspb.Message.addToRepeatedWrapperField(this, 3, opt_value, proto.Message, opt_index);
};


proto.ComMessage.prototype.clearPayloadList = function() {
  this.setPayloadList([]);
};


/**
 * repeated Message req_messages = 4;
 * @return {!Array<!proto.Message>}
 */
proto.ComMessage.prototype.getReqMessagesList = function() {
  return /** @type{!Array<!proto.Message>} */ (
    jspb.Message.getRepeatedWrapperField(this, proto.Message, 4));
};


/** @param {!Array<!proto.Message>} value */
proto.ComMessage.prototype.setReqMessagesList = function(value) {
  jspb.Message.setRepeatedWrapperField(this, 4, value);
};


/**
 * @param {!proto.Message=} opt_value
 * @param {number=} opt_index
 * @return {!proto.Message}
 */
proto.ComMessage.prototype.addReqMessages = function(opt_value, opt_index) {
  return jspb.Message.addToRepeatedWrapperField(this, 4, opt_value, proto.Message, opt_index);
};


proto.ComMessage.prototype.clearReqMessagesList = function() {
  this.setReqMessagesList([]);
};


