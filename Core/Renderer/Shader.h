/*
 * Shader.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/29/2025
 */

#ifndef RIFT_SHADER_H
#define RIFT_SHADER_H

namespace Rift {

    class Shader {
    public:
        Shader( const std::string &vertexSrc, const std::string &fragmentSrc );
        ~Shader();

        void Bind() const;
        void Unbind() const;

    private:
        uint32_t rendererID;
    };

} // namespace Rift

#endif // RIFT_SHADER_H
