/*
 * Copyright (c) 2022, Oracle and/or its affiliates. All rights reserved.
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
package test.javafx.scene.control;

import javafx.scene.AccessibleRole;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Dialog;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.assertEquals;

/** Tests for the {@link Dialog} class. */
public class DialogTest {

    private Dialog<ButtonType> dialog;

    @Before
    public void setUp() {
        dialog = new Dialog<>();
    }

    @After
    public void cleanUp() {
        // Set a dummy result so the dialog can be closed.
        dialog.setResult(new ButtonType(""));
        dialog.hide();
    }

    @Test
    public void testAccessibleRole() {
        assertEquals(AccessibleRole.DIALOG, dialog.getDialogPane().getAccessibleRole());
    }
}

