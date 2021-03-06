#pragma once

#include <mutex>

#include "mavlink_include.h"
#include "plugins/offboard/offboard.h"
#include "plugin_impl_base.h"
#include "system.h"

namespace mavsdk {

class OffboardImpl : public PluginImplBase {
public:
    OffboardImpl(System& system);
    ~OffboardImpl();

    void init() override;
    void deinit() override;

    void enable() override;
    void disable() override;

    Offboard::Result start();
    Offboard::Result stop();

    void start_async(Offboard::result_callback_t callback);
    void stop_async(Offboard::result_callback_t callback);

    bool is_active() const;

    void set_position_ned(Offboard::PositionNEDYaw position_ned_yaw);
    void set_velocity_ned(Offboard::VelocityNEDYaw velocity_ned_yaw);
    void set_velocity_body(Offboard::VelocityBodyYawspeed velocity_body_yawspeed);
    void set_attitude(Offboard::Attitude attitude);
    void set_attitude_rate(Offboard::AttitudeRate attitude_rate);
    void set_attitude_yaw_rate(Offboard::AttitudeYawRate attitude_yaw_rate);
    void set_quaternion(Offboard::Quaternion quaternion);
    void set_quaternion_yaw_rate(Offboard::QuaternionYawRate quaternion_yaw_rate);
    void set_roll_pitch_altitude(Offboard::RollPitchAltitude roll_pitch_altitude);
    void set_actuator_control(Offboard::ActuatorControl actuator_control);

    OffboardImpl(const OffboardImpl&) = delete;
    OffboardImpl& operator=(const OffboardImpl&) = delete;

private:
    void send_position_ned();
    void send_velocity_ned();
    void send_velocity_body();
    void send_attitude_rate();
    void send_attitude();
    void send_attitude_yaw_rate();
    void send_quaternion();
    void send_quaternion_yaw_rate();
    void send_roll_pitch_altitude();
    void send_actuator_control();
    void send_actuator_control_message(const float* controls, uint8_t group_number = 0);

    void process_heartbeat(const mavlink_message_t& message);
    void receive_command_result(
        MAVLinkCommands::Result result, const Offboard::result_callback_t& callback);

    static Offboard::Result offboard_result_from_command_result(MAVLinkCommands::Result result);

    void stop_sending_setpoints();

    Time _time{};

    mutable std::mutex _mutex{};
    enum class Mode {
        NOT_ACTIVE,
        POSITION_NED,
        VELOCITY_NED,
        VELOCITY_BODY,
        ATTITUDE,
        ATTITUDE_RATE,
        ATTITUDE_YAW_RATE,
        QUATERNION,
        QUATERNION_YAW_RATE,
        ROLL_PITCH_ALTITUDE,
        ACTUATOR_CONTROL
    } _mode = Mode::NOT_ACTIVE;
    Offboard::PositionNEDYaw _position_ned_yaw{};
    Offboard::VelocityNEDYaw _velocity_ned_yaw{};
    Offboard::VelocityBodyYawspeed _velocity_body_yawspeed{};
    Offboard::Attitude _attitude{};
    Offboard::AttitudeRate _attitude_rate{};
    Offboard::AttitudeYawRate _attitude_yaw_rate{};
    Offboard::Quaternion _quaternion{};
    Offboard::QuaternionYawRate _quaternion_yaw_rate{};
    Offboard::ActuatorControl _actuator_control{};
    Offboard::RollPitchAltitude _roll_pitch_altitude{};
    dl_time_t _last_started{};

    void* _call_every_cookie = nullptr;

    const float SEND_INTERVAL_S = 0.05f;
};

} // namespace mavsdk
