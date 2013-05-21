/* 
 * Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

package javafx.scene.paint;

/**
Builder class for javafx.scene.paint.Color
@see javafx.scene.paint.Color
@deprecated This class is deprecated and will be removed in the next version
*/
@javax.annotation.Generated("Generated by javafx.builder.processor.BuilderProcessor")
@Deprecated
public class ColorBuilder<B extends javafx.scene.paint.ColorBuilder<B>> implements javafx.util.Builder<javafx.scene.paint.Color> {
    protected ColorBuilder() {
    }
    
    /** Creates a new instance of ColorBuilder. */
    @SuppressWarnings({"deprecation", "rawtypes", "unchecked"})
    public static javafx.scene.paint.ColorBuilder<?> create() {
        return new javafx.scene.paint.ColorBuilder();
    }
    
    private double blue;
    /**
    Set the value of the {@link javafx.scene.paint.Color#getBlue() blue} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B blue(double x) {
        this.blue = x;
        return (B) this;
    }
    
    private double green;
    /**
    Set the value of the {@link javafx.scene.paint.Color#getGreen() green} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B green(double x) {
        this.green = x;
        return (B) this;
    }
    
    private double opacity = 1;
    /**
    Set the value of the {@link javafx.scene.paint.Color#getOpacity() opacity} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B opacity(double x) {
        this.opacity = x;
        return (B) this;
    }
    
    private double red;
    /**
    Set the value of the {@link javafx.scene.paint.Color#getRed() red} property for the instance constructed by this builder.
    */
    @SuppressWarnings("unchecked")
    public B red(double x) {
        this.red = x;
        return (B) this;
    }
    
    /**
    Make an instance of {@link javafx.scene.paint.Color} based on the properties set on this builder.
    */
    public javafx.scene.paint.Color build() {
        javafx.scene.paint.Color x = new javafx.scene.paint.Color(this.red, this.green, this.blue, this.opacity);
        return x;
    }
}
